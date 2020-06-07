// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#ifndef ETH_H
#define ETH_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdk/src/cgame/cg_local.h"

#define ETH_VERSION "0.1"

// Here all publics functions/vars common to all files

// Cvars
vmCvar_t eth_wallHack;

// systrap.c
void wrap_trap_Cvar_Register(vmCvar_t *vmCvar, const char *varName, const char *defaultValue, int flags);
void wrap_trap_Cvar_Update(vmCvar_t *vmCvar );
void wrap_trap_CG_SendConsoleCommand(const char *text);

#endif // ETH_H
