#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

unusedStaff(char** data)
{
	printf("Searching unused vars and functions:\n\n");

	int result[sizeOfResult][2] = { 0 };
	char Types[5][6] = { {"int"}, {"char"}, {"double"}, {"float"}, {"void"} };

	int step = 0;
	while (step < 5) {
		search(Types[step], data, result);
		findStaff(data, result, Types[step]);
		step++;
	}

	printf("\n------------------------------\n\n");
}

findStaff(char** data, int result[][2], char* needle)
{
	int sizeOfNeedle = strlen(needle);
	int step = 0;

	while (result[step][0]) {

		int line = result[step][0];
		int symbol = (result[step][1] + sizeOfNeedle + 1);

		checkName(data, line, symbol, step, result);

		step++;
	}
}

void checkName(char** data, int line, int symbol, int step, int result[][2])
{
	char name[sizeOfName] = { 0 };
	int point = 0;

	while ((data[line][symbol] >= 65 && data[line][symbol] <= 90) || (data[line][symbol] >= 97 && data[line][symbol] <= 122) || data[line][symbol] == '_') {
		name[point++] = data[line][symbol++];
	}

	char backward = data[line][symbol];

	if (backward != '(' && backward != '[') {
		int useless = findThisName(name, data);
		if (useless) {
			displayUnused(data, line, result, name, 1);
		}
	}
	else if (backward == '(') {
		int useless = findThisName(name, data);
		if (useless) {
			displayUnused(data, line, result, name, 2);
		}
	}
	else {
		return;
	}
	if (backward == ',') checkName(data, line, symbol + 2, step, result);
	return;
}

displayUnused(char** data, int line, int result[][2], char* name, int mode)
{
	if (mode == 1)
		printf("in line %3d unused var is \"%s\"\n", line, name);
	else printf("in line %3d unused func is \"%s\"\n", line, name);
}

int findThisName(char* name, char** data)
{
	if (!strcmp("main", name)) return 0;

	int resultOfName[sizeOfResult][2] = { 0 };
	search(name, data, resultOfName);

	if (!resultOfName[1][0]) return 1;
	else return 0;
}