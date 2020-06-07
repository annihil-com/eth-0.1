#!/bin/sh
# GPL License - see http://opensource.org/licenses/gpl-license.php
# Copyright 2005 eth team - don't forget to credits us

ET_SDK=et-linux-2.60-sdk.x86.run

die() {
	echo "Error: $1"
	exit 1
}

mkdir sdk || echo "Can't create sdk folder. Already here ?"
wget ftp://ftp.idsoftware.com/idstuff/et/sdk/$ET_SDK || die "Can't download sdk."
/bin/sh $ET_SDK --tar xfC sdk || die "Can't extract sdk."
