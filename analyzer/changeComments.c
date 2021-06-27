#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

changeComments(char** data)
{
	printf("Searching and correction comments:\n\n");

	int result[sizeOfResult][2] = { 0 };
	search("/*", data, result);

	int step = 0;
	while (result[step][0]) {
		checkComment(result[step][0], result[step][1], data);
		step++;
	}

	printf("\n------------------------------\n\n");
}

checkComment(int line, int symbol, char** data)
{
	int step = symbol + 2;
	while (data[line][step]) {
		if (data[line][step] == '*' && data[line][step + 1] == '/') {
			if (/*data[line][step + 2] != -1 || */data[line][step + 2]) takeOutOfLine(line, symbol, data);
			else replaceComment(line, symbol, data);
			printf("Was corrected in line %3d\n", line);
			return;
		}
		step++;
	}
	data[line][step] = '*';
	data[line][step + 1] = '/';
	data[line][step + 2] = '\0';
	replaceComment(line, symbol, data);
	checkComment(line + 1, 1, data);

	printf("Was corrected in line %3d\n", line);
}

replaceComment(int line, int symbol, char** data)
{
	char tempStr[sizeOfName] = { 0 };
	for (int i = 0; i < sizeOfName; i++)
		tempStr[i] = '\0';

	//tempStr[0] = '\t';
	tempStr[0] = '/';
	tempStr[1] = '/';
	int step = 2, point = symbol;
	while (data[line][point] != '*' && data[line][point + 1] != '/') {
		if (data[line][point] == '/' && data[line][point + 1] == '*') {
			point += 2;
			continue;
		}
		tempStr[step++] = data[line][point++];
	}
	deleteFromSymbol(line, symbol, data);
	addToData(line, symbol, data, tempStr);
}

takeOutOfLine(int line, int symbol, char** data)
{
	char tempStr[sizeOfName] = { 0 };
	for (int i = 0; i < sizeOfName; i++)
		tempStr[i] = '\0';

	//tempStr[0] = '\t';
	tempStr[0] = '/';
	tempStr[1] = '/';
	int step = 2, point = symbol, count = 0;
	while (data[line][point] != '*' && data[line][point + 1] != '/') {
		if (data[line][point] == '/' && data[line][point + 1] == '*') {
			point += 2;
			count += 2;
			continue;
		}
		tempStr[step++] = data[line][point++];
		count++;
	}
	deleteFromSymbolUntilSymbol(line, symbol, data, count);
	addToEnd(line, symbol, data, tempStr);
}

deleteFromSymbol(int line, int symbol, char** data)
{
	int step = symbol;
	while (data[line][step] != -1) {
		data[line][step] = '\0';
		step++;
	}
}

deleteFromSymbolUntilSymbol(int line, int symbol, char** data, int count)
{
	int step = symbol;
	count += 2;
	while (count != 0) {
		while (data[line][step] != -1) {
			data[line][step] = data[line][step + 1];
			step++;
		}
		step = symbol;
		count--;
	}
}

addToData(int line, int symbol, char** data, char* tempStr)
{
	int step = 0;
	int point = symbol;
	while (tempStr[step]) {
		data[line][point++] = tempStr[step++];
	}
}

addToEnd(int line, int symbol, char** data, char* tempStr)
{
	int point = symbol;
	while (data[line][point])
		point++;

	int step = 0;
	while (tempStr[step]) {
		data[line][point++] = tempStr[step++];
	}
	data[line][point] = '\0';
}