#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

checkCorrectNames(char** data)
{
	printf("Searching and correction names of vars and functions:\n\n");

	int result[sizeOfResult][2] = { 0 };
	char Types[5][6] = { {"int"}, {"char"}, {"double"}, {"float"}, {"void"} };

	int step = 0;
	while (step < 5) {
		search(Types[step], data, result);
		findNames(data, result, Types[step]);
		step++;
	}

	printf("\n------------------------------\n\n");
}

findNames(char** data, int result[][2], char* needle)
{
	int sizeOfNeedle = strlen(needle);
	int step = 0;

	while (result[step][0]) {

		int line = result[step][0];
		int symbol = (result[step][1] + sizeOfNeedle + 1);

		checkStaff(data, line, symbol, step, result);

		step++;
	}
}

void checkStaff(char** data, int line, int symbol, int step, int result[][2])
{
	char name[sizeOfName] = { 0 };
	int point = 0;

	while ((data[line][symbol] >= 65 && data[line][symbol] <= 90) || (data[line][symbol] >= 97 && data[line][symbol] <= 122) || data[line][symbol] == '_') {
		name[point++] = data[line][symbol++];
	}

	char backward = data[line][symbol];

	if (backward != '(') {
		renameName(name, data, 1, &symbol);
	}
	else if (backward == '(') {
		renameName(name, data, 2, &symbol);
	}
	else {
		return;
	}
	if (backward == ',') checkStaff(data, line, symbol + 2, step, result);
	return;
}

renameName(char* name, char** data, int mode, int* symbol)
{
	if (!strcmp("main", name)) return 0;

	char nameCopy[sizeOfName] = { 0 };
	strcpy(nameCopy, name);

	int changes = 0;
	int resultOfName[sizeOfResult][2] = { 0 };
	search(name, data, resultOfName);


	if ((name[0] <= 90 && name[0] >= 65) && mode == 1) {
		int step = 0;
		while (resultOfName[step][0]) {
			data[resultOfName[step][0]][resultOfName[step][1]] += 32;
			step++;
		}
		name[0] += 32;
		changes++;
	}

	if ((name[0] <= 122 && name[0] >= 97) && mode == 2) {
		int step = 0;
		while (resultOfName[step][0]) {
			data[resultOfName[step][0]][resultOfName[step][1]] -= 32;
			step++;
		}
		name[0] -= 32;
		changes++;
	}

	int point = 0;
	while (name[point]) {
		if (name[point] == '_') {
			int step = 0;
			while (resultOfName[step][0]) {
				*symbol -= 1;
				deleteLetter(point, resultOfName[step][0], resultOfName[step][1], data);
				step++;
			}
			int subpoint = point;
			if (name[subpoint + 1] <= 122 && name[subpoint + 1] >= 97) name[subpoint + 1] -= 32;
			while (name[subpoint]) {
				name[subpoint] = name[subpoint + 1];
				subpoint++;
			}
			changes++;
		}
		point++;
	}

	if (changes) displayRightName(name, nameCopy);
}

deleteLetter(int point, int line, int symbol, char** data)
{
	int step = (symbol + point);
	if (data[line][step + 1] <= 122 && data[line][step + 1] >= 97) data[line][step] -= 32;
	while (data[line][step] != -1) {
		data[line][step] = data[line][step + 1];
		step++;
	}
}

displayRightName(char* name, char* nameCopy)
{
	printf("\"%s\" => \"%s\"\n", nameCopy, name);
}