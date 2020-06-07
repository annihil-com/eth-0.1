// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#include "cg_main.h"

void wrap_CG_R_AddRefEntityToScene(refEntity_t *re) {
	if(re->frame && re->entityNum < MAX_CLIENTS && re->reFlags != ET_CORPSE) {
		if (!(re->renderfx & RF_DEPTHHACK ) && eth_wallHack.integer) {
			re->renderfx |= RF_DEPTHHACK | RF_NOSHADOW;
		}
	}
}

void wrap_CG_DrawActiveFrame(void) {
	UpdateCvars();
}

void wrap_CG_Init(void) {
	RegisterCvars();
}
