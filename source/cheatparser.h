#ifndef CHEATPARSER_H
#define CHEATPARSER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <string>

extern "C" {
#include <elm.h>
#include <usync.h>
}

#include "common.h"
#include "netconsole.h"

#define MAX_ENTRIES 500

struct cheatCodeEntry
{
	char name[256];
	int numCodes;
	char *codes[100];
};

struct cheatCodeList
{
	char gameId[7];
	char gameName[256];
	int numEntries;
	cheatCodeEntry *entries[MAX_ENTRIES];
};

cheatCodeList *parseCode(FILE*);
void nukeList(cheatCodeList*);

#endif