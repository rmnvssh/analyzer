#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"


int main()
{
	char** firstFile;
	char** secondFile;
	char** firstHeader;
	char** thirdFile;
	int result[sizeOfResult][2] = { 0 };	//в result записываются номеро строк с совпадениями

	firstFile = readFile(1);
	secondFile = readFile(2);
	firstHeader = readFile(3);
	thirdFile = readFile(4);

	unusedStaff(firstFile);
	checkCorrectNames(firstFile);
	nestedLoopsAndLooping(firstFile);
	recursion(firstFile);
	//changeComments(firstFile);
	//functionCallGraph(secondFile, thirdFile);

	writeFile(firstFile, 1);
	writeFile(secondFile, 2);
	writeFile(firstHeader, 3);

	freeAll(firstFile, secondFile, firstHeader);

	return 0;
}

char** readFile(int mode)
{
	FILE* input;
	char tempStr[100] = { 0 };

	switch (mode)
	{
	case 1:
		input = fopen("files/FirstFile.c", "r+");
		break;
	case 2:
		input = fopen("files/SecondFile.c", "r+");
		break;
	case 3:
		input = fopen("files/FirstHeader.h", "r+");
		break;
	case 4:
		input = fopen("files/ThirdFile.c", "r+");
		break;
	default:
		input = 0;
		break;
	}

	char** tempFile = { 0 };
	tempFile = (char**)malloc(length * sizeof(char*));
	for (int i = 0; i < length; i++) {
		tempFile[i] = (char*)malloc(width * sizeof(char));
		for (int j = 0; j < width; j++)
			tempFile[i][j] = -1;
	}

	int step = 0;
	if (input != NULL) {
		while (!feof(input))
		{
			fgets(tempStr, 100, input);
			int len = (strlen(tempStr) - 1);
			if (tempStr[len] == '\n')
				tempStr[len] = '\0';
			strcpy(tempFile[step++], tempStr);
		}

		fclose(input);
	}
	return tempFile;
}

writeFile(char** data, int mode)
{
	FILE* output;
	switch (mode)
	{
	case 1:
		output = fopen("files/outFirstFile.c", "wt");
		break;
	case 2:
		output = fopen("files/outSecondFile.c", "wt");
		break;
	case 3:
		output = fopen("files/outFirstHeader.h", "wt");
		break;
	default:
		output = 0;
		break;
	}

	int step = 0;
	while (data[step][0] != -1) {
		fprintf(output, "%s", data[step]);
		fprintf(output, "\n");
		step++;
	}
}


freeAll(char** firstFile, char** secondFile, char** firstHeader)
{
	for (int i = 0; i < length; i++)
		free(firstFile[i]);
	free(firstFile);

	for (int i = 0; i < length; i++)
		free(secondFile[i]);
	free(secondFile);

	for (int i = 0; i < length; i++)
		free(firstHeader[i]);
	free(firstHeader);
}
