// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#include "eth.h"
#include "hook.h"

void wrap_trap_Cvar_Register(vmCvar_t *vmCvar, const char *varName, const char *defaultValue, int flags) {
	orig_syscall(CG_CVAR_REGISTER, vmCvar, varName, defaultValue, flags);
}

void wrap_trap_Cvar_Update( vmCvar_t *vmCvar) {
	orig_syscall(CG_CVAR_UPDATE, vmCvar);
}

void wrap_trap_CG_SendConsoleCommand(const char *text) {
	orig_syscall(CG_SENDCONSOLECOMMAND, text);
}
