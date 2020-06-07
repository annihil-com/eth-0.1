// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#include "hook.h"

#define DEBUG

// Detour function take from ogc3-q3
#define unprotect(addr,len) (mprotect(addr,len,PROT_READ|PROT_WRITE|PROT_EXEC))
#define reprotect(addr,len) (mprotect(addr,len,PROT_READ|PROT_EXEC))
#define GET_PAGE(a) ((void*)(((unsigned long)a)&0xfffff000))
#define undetour_function(orig,tramp) do {\
	memcpy(orig,tramp,5);\
	reprotect(GET_PAGE(orig),4096);\
	} while( 0 )
void *detour_function(void *orig, void *det, int len, unsigned char *tramp) {
	if (len < 5)
		return 0;
	if (!tramp) {
		tramp = (unsigned char *) malloc(len + 5);
		memcpy(tramp, orig, len);
		tramp[len] = 0xE9;
		*((void **) (tramp + len + 1)) = (void *) ((((uint) orig) + len) - (uint) (tramp + len + 5));
	}
	unprotect(GET_PAGE(orig), 4096);
	*((unsigned char *) orig) = 0xE9;
	*((void **) ((uint) orig + 1)) = (void *) (((uint) det) - (((uint) orig) + 5));
	return tramp;
}

// Lib constructor
void __attribute__ ((constructor)) my_init(void) {
	// The only hard hook need
	if (orig_dlsym == NULL) {
		orig_dlsym = detour_function((void *)dlsym, &wrap_dlsym, 0x5, NULL);
		//undetour_function((void*)dlsym, wrap_dlsym); // TODO: Why don't work ?
	}
	printf("ETH: start: %i %x %i %x %i %x\n", sizeof(dlsym), (unsigned int)&dlsym, sizeof(wrap_dlsym), (unsigned int)&wrap_dlsym, sizeof(dlopen), (unsigned int)&dlopen);
	printf("ETH: start: %i %i\n", sizeof(unsigned int), sizeof(void *));
}

// The main hooker
void *wrap_dlsym(void *handle, const char *symbol) {
	#ifdef DEBUG
		if (orig_dlsym == NULL)
			printf("ETH: wrap_dlsym: orig_dlsym was NULL");
		printf("ETH: wrap_dlsym: try to load function '%s' at library handle 0x%x\n", symbol, (unsigned int)handle);
	#endif // DEBUG
	void *result = orig_dlsym(handle, symbol);
	if (!strcmp(symbol, "dllEntry")) {
		#ifdef DEBUG
			printf("ETH: wrap_dlsym: dllEntry found at 0x%x at lib handle 0x%x\n", (unsigned int)result, (unsigned int)handle);
		#endif // DEBUG
		orig_dllEntry = result;
		return wrap_dllEntry;
	} else if (!strcmp(symbol, "vmMain") && handle == cgameLibHandle) {
		#ifdef DEBUG
			printf("ETH: wrap_dlsym: CG_vmMain is found at 0x%x in lib handle 0x%x\n", (unsigned int)result, (unsigned int)handle);
		#endif // DEBUG
		orig_CG_vmMain = result;
		return wrap_CG_vmMain;
	}
	return result;
}

void *dlopen(const char *filename, int flag) {
	// Init orig_dlopen hooking if not already done
	if (orig_dlopen == NULL)
		orig_dlopen = (void *(*)(const char *filename, int flag)) dlsym(RTLD_NEXT, "dlopen");
	void *result = orig_dlopen(filename, flag);
	#ifdef DEBUG
		if (orig_dlsym == NULL)
			printf("ETH: dlopen: orig_dlopen was NULL");
		printf("ETH: dlopen: a library is try to load '%s' at %x\n", filename, (unsigned int)result);
	#endif // DEBUG
	// Return if dlopen fail
	if (result == NULL) // FIXME: Really need ? humm...
		return NULL;
	
	if ((filename != NULL) && strstr(filename, CGAME_LIB_NAME))
		cgameLibHandle = result;
	
	return result;
}

int wrap_CG_vmMain(int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11 ) {
	#ifdef DEBUG
		//printf("ETH: wrap_CG_vmMain: command '%i' is executed\n", command); // Very annoying
	#endif // DEBUG
	
	int result = orig_CG_vmMain(command, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
	switch (command) {
		case CG_INIT:
			wrap_CG_Init();
			return 0;
		case CG_DRAW_ACTIVE_FRAME:
			wrap_CG_DrawActiveFrame();
			return 0;
	}
	return result;
}

void wrap_dllEntry(int (*syscallptr) (int arg,...)) {
	#ifdef DEBUG
		printf("ETH: wrap_dllEntry: syscall found at 0x%x\n", (unsigned int)syscallptr);
	#endif // DEBUG
	orig_syscall = syscallptr;
	orig_dllEntry(wrap_syscall);
}

int wrap_syscall(int command, ...) {
	#ifdef DEBUG
		//printf("ETH: wrap_syscall: command '%i' is executed\n", command); // Very annoying
	#endif // DEBUG
	
	// Get all originals arguments to send them to the original function
	int arg[10];
	va_list arglist;
	va_start(arglist, command);
	int i, j;
	for (i=9, j=0; i > 0; i--)
		arg[j++] = va_arg(arglist, int);
	va_end(arglist);
	
	switch (command) {
		case CG_R_ADDREFENTITYTOSCENE:
			wrap_CG_R_AddRefEntityToScene((refEntity_t *)arg[0]);
	}
	
	return orig_syscall(command, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
}
