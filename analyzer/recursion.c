#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

int normalSymbol(char c)
{
	if (c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return 1;
	if (c >= '0' && c <= '9' || c == '*')
		return 2;
	return 0;
}

recursion(char** file1)
{
	char functionNames[sizeOfResult][sizeOfResult] = { 0 };
	int result[sizeOfResult][4];
	int n = 0;
	int rec = 0;
	functionSearch(file1, functionNames, result, &n);
	for (int i = 0; i < n; i++)
	{
		if (functionNames[i][0] != 0)
		{
			char** shortFile = { 0 };
			shortFile = (char**)malloc(length * sizeof(char*));
			for (int l = 0; l < length; l++) {
				shortFile[l] = (char*)malloc(width * sizeof(char));
				for (int m = 0; m < width; m++)
					shortFile[l][m] = -1;
			}
			for (int m = 0; m < result[i][2]; m++)
			{
				shortFile[m][0] = '0';
			}
			for (int k = 0; k <= result[i][1]; k++)
			{
				shortFile[result[i][0]][k] = '0';
			}
			for (int m = result[i][0]; m <= result[i][2]; m++)
				for (int k = 0; k < width; k++)
				{
					if (m == result[i][0] && k == 0)
					{
						k = result[i][1];
					}
					shortFile[m][k] = file1[m][k];
				}
			int r[sizeOfResult][2] = { 0 };
			search(functionNames[i], shortFile, r);
			if (r[0][0] != 0)
				rec++;
			for (int j = i + 1; j < n; j++)
			{
				r[0][0] = 0;
				if (functionNames[j][0] != 0)
				{
					search(functionNames[j], shortFile, r);
					if (r[0][0] != 0)
					{
						r[0][0] = 0;
						char** shortFile1 = { 0 };
						shortFile1 = (char**)malloc(length * sizeof(char*));
						for (int l = 0; l < length; l++) {
							shortFile1[l] = (char*)malloc(width * sizeof(char));
							for (int m = 0; m < width; m++)
								shortFile1[l][m] = -1;
						}
						for (int m = 0; m < result[j][2]; m++)
						{
							shortFile1[m][0] = '0';
						}
						for (int k = 0; k <= result[j][1]; k++)
						{
							shortFile1[result[j][0]][k] = '0';
						}
						for (int m = result[j][0]; m <= result[j][2]; m++)
							for (int k = 0; k < width; k++)
							{
								if (m == result[j][0] && k == 0)
								{
									k = result[j][1];
								}
								shortFile1[m][k] = file1[m][k];
							}
						search(functionNames[i], shortFile1, r);
						if (r[0][0] != 0)
							rec++;
						free(shortFile1);
					}
				}
			}
			if (rec > 0) {
				printf("Recursion take place in function %s\n", functionNames[i]);
			}
			rec = 0;
			free(shortFile);
		}
	}
	printf("\n------------------------------\n\n");
}

functionSearch(char** file1, char functionNames[sizeOfResult][sizeOfResult], int result[sizeOfResult][4], int* n)
{
	int step1 = 0, step2 = 0;
	while (file1[step1][0] != -1)
	{
		while (file1[step1][step2] == ' ' || file1[step1][step2] == '\t')
			step2++;
		int i = 0;
		int k = 0;
		if (normalSymbol(file1[step1][step2]) == 1)
		{
			char name[sizeOfResult] = { 0 };
			int res[2] = { 0 };
			int s = 0;
			while (normalSymbol(file1[step1][step2]) != 0)
			{
				name[s] = file1[step1][step2];
				s++;
				step2++;
				if ((file1[step1][step2] == ' ' || file1[step1][step2] == '\t') && k == 0)
				{
					k++;
					step2++;
					s = 0;
				}
			}
			k = 0;
			if (file1[step1][step2] == '(')
			{
				while (file1[step1][step2] != ')')
					step2++;
				step2++;
				while (file1[step1][step2] == ' ' || file1[step1][step2] == '\t')
					step2++;
				if (file1[step1][step2] != '{')
				{
					step1++;
					step2 = 0;
				}
				if (file1[step1][step2] == '{')
				{
					k++;
					res[0] = step1;
					res[1] = step2;
					step2++;
					while (k != 0)
					{
						if (file1[step1][step2] == '{')
							k++;
						if (file1[step1][step2] == '}')
							k--;
						if (k == 0)
						{
							for (int u = 0; u < s; u++)
								functionNames[*n][u] = name[u];
							result[*n][0] = res[0];
							result[*n][1] = res[1];
							result[*n][2] = step1;
							result[*n][3] = step2;
							*n += 1;
							i = 1;
						}
						step2++;
						if (file1[step1][step2] == -1)
						{
							step1++;
							step2 = 0;
						}
					}
				}
			}
		}
		step1++;
		step2 = 0;
	}
}