#pragma once

#define size 100
#define length 10		//количество строк в input

int push(double stack[], int point, double digit);
int pop(double stack[], int point);
int is_empty(double stack[], int point);
double top(double stack[], int point);

double distributor(char* expression, char** data);

int is_operator(char symb);
int prio(char symb);
double calculate(double a, double b, char operator);

double calcFunction(char* expression, int step, int func, char** data);
