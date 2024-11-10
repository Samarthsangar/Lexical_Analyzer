#ifndef ERRORCHECK_H
#define ERRORCHECK_H

#define MAX_TOKEN_SIZE 100
#define DATA_TYPES 5

typedef enum {
    e_sucesss,
    e_failur
}Validat;

Validat ErrorCheck();
Validat isHeader(char arr[MAX_TOKEN_SIZE]);
Validat isPrintf(char arr[MAX_TOKEN_SIZE]);
Validat isInt(char arr[MAX_TOKEN_SIZE]);
Validat isFloat(char arr[MAX_TOKEN_SIZE]);

#endif