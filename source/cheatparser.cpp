//handles parsing of .txt cheat files

#include "cheatparser.h"

cheatCodeList *parseCode(FILE *fp)
{
	cheatCodeList *list = new cheatCodeList; //init everything
	memset(list, 0, sizeof(cheatCodeList));
	int i;
	char c, c2;
	char temp[256];
	fgets((char*)list->gameId, 6, fp);
	c = fgetc(fp);
	cheatCodeEntry *currEntry;
	fgets((char*)&list->gameName, 256, fp);
	c = fgetc(fp); //remove newline
	while (!feof(fp))
	{
		currEntry = new cheatCodeEntry;
		memset(currEntry, 0, sizeof(cheatCodeEntry));
		fgets((char*)&temp, 256, fp);
		strncpy(currEntry->name, (char*)&temp, strlen((char*)&temp)-1);
		for(i=0;i<100;i++)
		{
			fgets((char*)&temp, 256, fp);
			if (strlen(temp) != 18)
				break;
			currEntry->codes[i] = new char[18];
			strncpy(currEntry->codes[i], (char*)&temp, 17);
			currEntry->numCodes++;
		}
		c = '\n';
		while(!feof(fp))
		{
			c2 = fgetc(fp);
			if ((c == '\n') && (c2 == '\n'))
				break;
			c = c2;
		}
		if (currEntry->numCodes == 0)
			continue;
		list->entries[list->numEntries] = currEntry;
		list->numEntries++;
	}
	return list;
}

void nukeList(cheatCodeList *list)
{
	int i,j;
	for (i=0;i<list->numEntries;i++)
	{
		for (j=0;j<list->entries[i]->numCodes;j++)
		{
			delete[] list->entries[i]->codes[j];
		}
		delete[] list->entries[i];
	}
	delete list;
}