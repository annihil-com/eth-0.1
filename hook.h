// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#ifndef HOOK_H
#define HOOK_H

#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/mman.h>

#include "eth.h"
#include "cg_main.h"

#define CGAME_LIB_NAME "cgame.mp.i386.so"
#define DL_LIB_NAME "libdl.so"

void *cgameLibHandle;

// system lib hooked functions
void *(*orig_dlopen) (const char *filename, int flag);

void *(*orig_dlsym) (void *handle, const char *symbol);
void *wrap_dlsym(void *handle, const char *symbol);

// game lib hooked functions
void (*orig_dllEntry) (int (*syscallptr) (int arg,... ));
void wrap_dllEntry(int ( *syscallptr) (int arg,... ));

int (*orig_syscall) (int command, ...); // 0x8084f50 and never change
int wrap_syscall(int command, ...);

int (*orig_CG_vmMain) (int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);
int wrap_CG_vmMain(int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);

void *detour_function(void *, void *, int, unsigned char *);

#endif // HOOK_H
