#!/bin/sh
# GPL License - see http://opensource.org/licenses/gpl-license.php
# Copyright 2005 eth team - don't forget to credits us

LOG_FILE=eth.log

getinfo() {
	echo "ETH: sh export" >> $LOG_FILE
	export >> $LOG_FILE
	echo "ETH: sh set" >> $LOG_FILE
	set >> $LOG_FILE
	echo "ETH: GCC Version" >> $LOG_FILE
	gcc --version >> $LOG_FILE
	echo "ETH: /usr/lib filelist" >> $LOG_FILE
	ls -la /usr/lib >> $LOG_FILE
}

echo "Debug mode for beta test: no more output here. See eth.log.gz"
rm -f $LOG_FILE $LOG_FILE.gz
getinfo >> $LOG_FILE
export LD_PRELOAD=./libETH.so
./et.x86 $* >> $LOG_FILE 2>&1
unset LD_PRELOAD
gzip eth.log
