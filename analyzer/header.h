#pragma once

#define length 300
#define width 100
#define sizeOfResult 20
#define sizeOfName 20

char** readFile(int mode);
writeFile(char** data, int mode);
freeAll(char** firstFile, char** secondFile, char** firstHeader);


char** readFile(int mode);
freeAll(char** firstFile, char** secondFile, char** firstHeader);

search(char* needle, char** haystack, int result[][2]);
int searchInLine(char* needle, char* haystack, int* offsetTable);
addToResult(int index, int row, int result[][2]);
letterExist(char letter, char* needle);
checkWord(char* haystack, int step, int sizeOfNeedle);

unusedStaff(char** data);
findStaff(char** data, int result[][2], char* needle);
void checkName(char** data, int line, int symbol, int step, int result[][2]);
displayUnused(char** data, int line, int result[][2], char* name, int mode);
int findThisName(char* name, char** data);

checkCorrectNames(char** data);
findNames(char** data, int result[][2], char* needle);
void checkStaff(char** data, int line, int symbol, int step, int result[][2]);
renameName(char* name, char** data, int mode, int* symbol);
deleteLetter(int point, int line, int symbol, char** data);

//nestedLoops(char** file1);
nestedLoopsAndLooping(char** file1);
loops(char** file1, int* count);
endOfLoop(char** file1, int firstLetter[2], int lastLetter[2]);

recursion(char** file1);

changeComments(char** data);
checkComment(int line, int symbol, char** data);
replaceComment(int line, int symbol, char** data);
takeOutOfLine(int line, int symbol, char** data);
deleteFromSymbol(int line, int symbol, char** data);
deleteFromSymbolUntilSymbol(int line, int symbol, char** data, int count);
addToData(int line, int symbol, char** data, char* tempStr);
addToEnd(int line, int symbol, char** data, char* tempStr);