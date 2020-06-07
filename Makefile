# GPL License - see http://opensource.org/licenses/gpl-license.php
# Copyright 2005 eth team - don't forget to credits us

CC = gcc
LD = gcc
CFLAGS = -g -Wall -fPIC
LDFLAGS = -ldl -shared

RM = /bin/rm -f

OBJS = cg_main.o cvars.o hook.o q_math.o systrap.o
PROG = libETH.so

# Main rule
all: $(PROG)

# Link
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

cg_main.o: cg_main.c
	$(CC) $(CFLAGS) -c cg_main.c
cvars.o: cvars.c
	$(CC) $(CFLAGS) -c cvars.c
hook.o: hook.c
	$(CC) $(CFLAGS) -c hook.c
q_math.o: sdk/src/game/q_math.c
	$(CC) $(CFLAGS) -c sdk/src/game/q_math.c
systrap.o: systrap.c
	$(CC) $(CFLAGS) -c systrap.c

clean:
	$(RM) $(PROG) $(OBJS)
