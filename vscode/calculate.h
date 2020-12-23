#include<stdio.h>
char * calculate(char * equ);
unsigned short int is_digit(char ch);
unsigned short int is_operation(char ch);
unsigned short int is_x(char ch);
void secondPriority(double *numbuffer, char *opbuffer, double *result);
void thirdPriority(double *numbuffer, char *opbuffer, double *result);
void firstPriority(double *numbuffer, char *opbuffer, double *result);
void bracketSolve(double *numbuffer, char *opbuffer, double *result);
void calculateEx(double *numbuffer, char *opbuffer, double *result);
extern double dmax;
