// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#include "eth.h"

typedef struct {
    vmCvar_t *vmCvar;
    char *cvarName;
    char *defaultString;
    int cvarFlags;
} cvarTable_t;

void RegisterCvars(void);
void UpdateCvars(void);
