#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

nestedLoopsAndLooping(char** file1)
{
	int count = 0;
	loops(file1, &count);
	printf("Maximum nesting of loops: %d\n", count);
	looping(file1);
	printf("\n------------------------------\n\n");
}

loops(char** file1, int* count)
{
	int resultFor[sizeOfResult][2] = { 0 };
	search("for", file1, resultFor);
	int resultWhile[sizeOfResult][2] = { 0 };
	search("while", file1, resultWhile);
	int countFor = 0, countWhile = 0;
	for (int i = 0; i < sizeOfResult; i++)
		if (resultFor[i][0] == 0 && resultFor[i][1] == 0)
		{
			countFor = i;
			i = sizeOfResult;
		}
	for (int i = 0; i < sizeOfResult; i++)
		if (resultWhile[i][0] == 0 && resultWhile[i][1] == 0)
		{
			countWhile = i;
			i = sizeOfResult;
		}
	int maxCount = *count;
	for (int i = 0; i < countFor; i++)
	{
		int lastLetter[2] = { 0 };
		int c = *count + 1;
		endOfLoop(file1, resultFor[i], lastLetter);
		resultFor[i][1]++;
		char** shortFile = { 0 };
		shortFile = (char**)malloc(length * sizeof(char*));
		for (int n = 0; n < length; n++)
		{
			shortFile[n] = (char*)malloc(width * sizeof(char));
			for (int j = 0; j < width; j++)
				shortFile[n][j] = -1;
		}
		for (int j = 0; j < lastLetter[0]; j++)
		{
			shortFile[j][0] = '0';
		}
		for (int k = 0; k <= resultFor[i][1]; k++)
		{
			shortFile[resultFor[i][0]][k] = '0';
		}
		for (int j = resultFor[i][0]; j <= lastLetter[0]; j++)
			for (int k = 0; k < width; k++)
			{
				if (j == resultFor[i][0] && k == 0)
				{
					k = resultFor[i][1];
				}
				shortFile[j][k] = file1[j][k];
			}
		loops(shortFile, &c);
		free(shortFile);
		if (c > maxCount) maxCount = c;
	}
	for (int i = 0; i < countWhile; i++)
	{
		int lastLetter[2] = { 0 };
		int c = *count + 1;
		endOfLoop(file1, resultWhile[i], lastLetter);
		resultWhile[i][1]++;
		char** shortFile = { 0 };
		shortFile = (char**)malloc(length * sizeof(char*));
		for (int i = 0; i < length; i++) {
			shortFile[i] = (char*)malloc(width * sizeof(char));
			for (int j = 0; j < width; j++)
				shortFile[i][j] = -1;
		}
		for (int j = 0; j < lastLetter[0]; j++)
		{
			shortFile[j][0] = '0';
		}
		for (int k = 0; k <= resultWhile[i][1]; k++)
		{
			shortFile[resultWhile[i][0]][k] = '0';
		}
		for (int j = resultWhile[i][0]; j <= lastLetter[0]; j++)
			for (int k = 0; k < width; k++)
			{
				if (j == resultWhile[i][0] && k == 0)
				{
					k = resultWhile[i][1];
				}
				shortFile[j][k] = file1[j][k];
			}
		loops(shortFile, &c);
		free(shortFile);
		if (c > maxCount) maxCount = c;
	}
	*count = maxCount;
}

looping(char** file1)
{
	int resultFor[sizeOfResult][2] = { 0 };
	search("for", file1, resultFor);
	int k = 0;
	while (resultFor[k][0] != 0)
	{
		int i = resultFor[k][0], j = resultFor[k][1];
		while (file1[i][j] != '(')
			j++;
		j++;
		int s = 0;
		while (file1[i][j] != ')')
		{
			if (file1[i][j] != ' ' && file1[i][j] != '\t' && file1[i][j] != ';')
				s++;
			j++;
		}
		if (s == 0)
		{
			int lastLetter[2] = { 0 };
			endOfLoop(file1, resultFor[k], lastLetter);
			char** shortFile = { 0 };
			shortFile = (char**)malloc(length * sizeof(char*));
			for (i = 0; i < length; i++) {
				shortFile[i] = (char*)malloc(width * sizeof(char));
				for (int j = 0; j < width; j++)
					shortFile[i][j] = -1;
			}
			for (j = 0; j < lastLetter[0]; j++)
			{
				shortFile[j][0] = '0';
			}
			for (i = 0; i <= resultFor[k][1]; i++)
			{
				shortFile[resultFor[k][0]][i] = '0';
			}
			for (j = resultFor[k][0]; j <= lastLetter[0]; j++)
				for (i = 0; i < width; i++)
				{
					if (j == resultFor[k][0] && i == 0)
					{
						i = resultFor[k][1];
					}
					shortFile[j][i] = file1[j][i];
				}
			int res[sizeOfResult][2] = { 0 };
			search("break", shortFile, res);
			if (res[0][0] == 0)
			{
				printf("Possible looping in line %d\n", resultFor[k][0]);
			}
			free(shortFile);
		}
		k++;
	}
	int resultWhile[sizeOfResult][2] = { 0 };
	search("while", file1, resultWhile);
	k = 0;
	while (resultWhile[k][0] != 0)
	{
		int i = resultWhile[k][0], j = resultWhile[k][1];
		while (file1[i][j] != '(')
			j++;
		j++;
		int s = 0;
		while (file1[i][j] != ')')
		{
			if (file1[i][j] != ' ' && file1[i][j] != '\t' && file1[i][j] != ';')
				s++;
			j++;
		}
		if (s == 0)
		{
			int lastLetter[2] = { 0 };
			endOfLoop(file1, resultWhile[k], lastLetter);
			resultWhile[k][1]++;
			char** shortFile = { 0 };
			shortFile = (char**)malloc(length * sizeof(char*));
			for (i = 0; i < length; i++) {
				shortFile[i] = (char*)malloc(width * sizeof(char));
				for (int j = 0; j < width; j++)
					shortFile[i][j] = -1;
			}
			for (j = 0; j < lastLetter[0]; j++)
			{
				shortFile[j][0] = '0';
			}
			for (i = 0; i <= resultWhile[k][1]; i++)
			{
				shortFile[resultWhile[k][0]][i] = '0';
			}
			for (j = resultWhile[k][0]; j <= lastLetter[0]; j++)
				for (i = 0; i < width; i++)
				{
					if (j == resultWhile[k][0] && i == 0)
					{
						i = resultWhile[k][1];
					}
					shortFile[j][i] = file1[j][i];
				}
			int r[sizeOfResult][2] = { 0 };
			search("break", shortFile, r);
			if (r[0][0] == 0)
			{
				printf("Possible looping in line %d\n", resultWhile[k][0]);
			}
			free(shortFile);
		}
		k++;
	}
}


endOfLoop(char** file1, int firstLetter[2], int lastLetter[2])
{
	int c = 0, k = 0;
	for (int i = firstLetter[0]; i < length; i++)
		for (int l = firstLetter[1]; l < width; l++)
		{
			if (file1[i][l] == '(')
				c++;
			if (file1[i][l] == ')')
				c--;
			if (c == 0)
			{
				if ((file1[i][l] == ';') && k == 0)
				{
					lastLetter[0] = i;
					lastLetter[1] = l;
					i = length;
					l = width;
				}
				else if (file1[i][l] == '{')
					k++;
				else if ((file1[i][l] == '}'))
				{
					k--;
					if (k == 0)
					{
						lastLetter[0] = i;
						lastLetter[1] = l;
						i = length;
						l = width;
					}
				}
			}
		}
}
