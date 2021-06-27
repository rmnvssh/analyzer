#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

typedef struct element {
	char name[sizeOfName];
	int count;
	struct element* list[sizeOfResult];
}element;

functionCallGraph(char** data, char** subData)
{
	printf("Function call graphs:\n\n");

	int result[sizeOfResult][2] = { 0 };
	search("main", data, result);
	element* main = (element*)malloc(sizeof(element));
	strcpy(main->name, "main");
	main->count = 0;

	checkFunc(result[0][0] + 1, data, subData, main);

	int step = 0, lenOfStr = (strlen(main->name) + 2);
	char spaces[100] = { 0 };

	while (step < lenOfStr)
		spaces[step++] = ' ';

	step = 0;
	while (step < main->count) {
		int point = 0;
		while (point < lenOfStr)
			spaces[point++] = ' ';

		printf("%s ", main->name);
		displayElements(main->list[step], spaces);
		nullifyName(spaces);
		step++;
	}

	printf("\n------------------------------\n\n");
}

displayElements(element* child, char* spaces)
{
	if (child->count == 0) {
		printf("=> %s\n", child->name);
		return;
	}

	int step = 0, lenOfStr = (strlen(child->name) + 3);
	printf("=> %s ", child->name);
	while (step < lenOfStr) {
		addToName(' ', spaces);
		step++;
	}

	step = 0;
	while (step < child->count) {
		if (step > 0) printf("%s", spaces);
		displayElements(child->list[step], spaces);
		//printf("%s", spaces);
		step++;
	}

	step = 0;
	while (spaces[step])
		step++;
	int point = 0;
	while (point < lenOfStr) {
		spaces[step--] = '\0';
		point++;
	}

	//printf("\n");
}

checkFunc(int step, char** data, char** subData, element* elem)
{
	if (data[step][0] == '{') step++;
	while (data[step][0] != '}') {
		checkLine(data[step], data, subData, elem);
		step++;
	}
}

checkLine(char* line, char** data, char** subData, element* elem)
{
	char nameOfFunc[sizeOfName] = { 0 };		//name();
	int step = 0;
	while (line[step]) {
		if ((line[step] >= 65 && line[step] <= 90) || (line[step] >= 97 && line[step] <= 122)) {
			addToName(line[step], nameOfFunc);
			if (line[step + 1] == '(') {
				elem->list[elem->count] = (element*)malloc(sizeof(element));
				strcpy(elem->list[elem->count]->name, nameOfFunc);
				elem->list[elem->count]->count = 0;
				findFunc(nameOfFunc, data, subData, elem->list[elem->count]);
				findFunc(nameOfFunc, subData, data, elem->list[elem->count]);
				elem->count++;
				return;
			}
		}
		else nullifyName(nameOfFunc);
		step++;
	}
}

copyName(char* name, char* strName)
{
	char tempName[sizeOfName] = { 0 };
	strcpy(name, tempName);
	strName = tempName;
}

addToName(char symbol, char* name)
{
	int step = 0;
	while (name[step])
		step++;
	name[step] = symbol;
}

nullifyName(char* name)
{
	int step = 0;
	while (name[step])
		name[step++] = '\0';
}

findFunc(char* name, char** data, char** subData, element* elem)
{
	int result[sizeOfResult][2] = { 0 };
	search(name, data, result);

	int step = 0;
	while (result[step][0] || result[step][1]) {
		int line = result[step][0];
		int symbol = result[step][1];

		if (data[line][symbol - 1] == ' ' && (data[line][symbol - 2] >= 97 && data[line][symbol - 2] <= 122)) {
			checkFunc(line + 1, data, subData, elem);
			return;
		}
		step++;
	}
}
