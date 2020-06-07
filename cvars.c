// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#include "cvars.h"

static cvarTable_t cvarTable[] = {
	{&eth_wallHack, "eth_wallhack", "1", CVAR_ARCHIVE}
};
static int cvarTableSize = sizeof(cvarTable) / sizeof(cvarTable[0]);

void RegisterCvars() {
	int i;
	cvarTable_t *cv;
	for (i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++)
		wrap_trap_Cvar_Register(cv->vmCvar, cv->cvarName, cv->defaultString, cv->cvarFlags);
}

void UpdateCvars(void) {
	int i;
	cvarTable_t *cv;
	for (i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++)
		wrap_trap_Cvar_Update(cv->vmCvar);
}
