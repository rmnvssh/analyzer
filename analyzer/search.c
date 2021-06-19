#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

search(char* needle, char** haystack, int result[][2])
{
	int lenOfNeedle = strlen(needle);
	int* offsetTable = (int*)malloc(lenOfNeedle * sizeof(int));
	int step = 0;

	for (int i = 0; i < sizeOfResult; i++)
	{
		result[i][0] = '\0';
		result[i][1] = '\0';
	}

	step = 0;
	int point = (lenOfNeedle - 1);
	while (needle[step + 1]) {
		offsetTable[step] = point;
		step++;
		point--;
	}
	offsetTable[step] = lenOfNeedle;

	step = 0;
	while (haystack[step][0] != -1) {
		int res = searchInLine(needle, haystack[step], offsetTable);
		if (res != -1) addToResult(step, res, result);
		step++;
	}
	free(offsetTable);
}

int searchInLine(char* needle, char* haystack, int* offsetTable)
{
	int step = (strlen(needle) - 1);
	int point = step;
	while (haystack[step] != -1) {
		while (needle[point] == haystack[step] && point >= 0) {
			point--;
			step--;
		}
		if (point < 0) {
			int checkFlag = checkWord(haystack, step, strlen(needle));
			if (checkFlag) return (step + 1);
			else {
				step += (strlen(needle) + 1);
				continue;
			}
		}

		point = letterExist(haystack[step], needle);
		if (point != -1)
			step += offsetTable[point];
		else step += strlen(needle);

		point = (strlen(needle) - 1);
	}
	return -1;
}

addToResult(int index, int row, int result[][2])
{
	int step = 0;
	while (result[step][0])
		step++;
	result[step][0] = index;
	result[step][1] = row;
}

letterExist(char letter, char* needle)
{
	int step = 0;
	while (needle[step]) {
		if (letter == needle[step])
			return step;
		else step++;
	}
	return -1;
}

checkWord(char* haystack, int step, int sizeOfNeedle)
{
	char front = haystack[step];
	char backward = haystack[step + sizeOfNeedle + 1];
	if ((front == ' ' || front == '\t' || front == '(' || front == '&' || front == '/' || step <= 0) && (backward == ' ' || backward == '\t' || backward == ')' || backward == '(' || backward == ';' || backward == ',' || backward == '+' || backward == -1))
		return 1;
	else return 0;
}