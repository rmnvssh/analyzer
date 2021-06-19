#pragma once

#define length 300
#define width 100
#define sizeOfResult 20
#define sizeOfName 20

char** readFile(int mode);
writeFile(char** data, int mode);
freeAll(char** firstFile, char** secondFile, char** firstHeader);

search(char* needle, char** haystack, int result[][2]);
int searchInLine(char* needle, char* haystack, int* offsetTable);
addToResult(int index, int row, int result[][2]);
letterExist(char letter, char* needle);
checkWord(char* haystack, int step, int sizeOfNeedle);

nestedLoopsAndLooping(char** file1);
loops(char** file1, int* count);
endOfLoop(char** file1, int firstLetter[2], int lastLetter[2]);