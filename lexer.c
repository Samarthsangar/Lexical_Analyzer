#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

/*Array of pointer*/
static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct" , "#define" , "extren",
    "static" , "scanf" , "printf" ,"auto" , "register" ,
};
static const char* directry ="#include<stdio.h>";
const char* operators = "+-*/%=!<>|&";
const char* specialCharacters = "#?:,;{}()[]";

/*Catacterising the token's*/
void categorizeToken(Token* token)
{
    /*Function call to check it is a keyword or not*/
    if(isKeyword(token->lexeme)==e_sucess)
    {
        token->type=KEYWORD;
        return;
    }
    /*Function call to check it is a operater or not*/
    else if(isOperator(token->lexeme)==e_sucess)
    {
        token->type=OPERATOR;
        return;
    }
    /*Function call to check it is a SpecialCharacter or not*/
    else if(isSpecialCharacter(token->lexeme)==e_sucess)
    {
        token->type=SPECIAL_CHARACTER;
        return;
    }
    /*Function call to check it is a Constant or not*/
    else if(isConstant(token->lexeme)==e_sucess)
    {
        token->type=CONSTANT;
        return;
    }
    /*Function call to check it is a Identifier or not*/
    else if(isIdentifier(token->lexeme)==e_sucess)
    {
        token->type=IDENTIFIER;
        return;
    }
    /*else return unknown*/
    else
    {
        token->type=UNKNOWN;
        return;
    }

}

/*Checking it is a keyword or not*/
int isKeyword(const char* str)
{
    for(int i=0; i<MAX_KEYWORDS; i++)
    {
        if(strcmp(str,keywords[i])==0)
            return e_sucess;
    }
    return e_failure;
}

/*Checking it is a Operator or not*/
int isOperator(const char* str)
{
    int len=strlen(str);
    for(int i=0; i<len; i++)
    {
        if((strchr(operators,str[i])!=NULL)&& len<4)
            return e_sucess;
    }
    return e_failure;
}

/*Checking it is a SpecialCharacter or not*/
int isSpecialCharacter(char *ch)
{
    if(strstr(specialCharacters,ch)!=NULL)
        return e_sucess;
    else
        return e_failure;
}
/*Checking it is a Constant or not*/
int isConstant(const char* str)
{
    int len=strlen(str);
    if(str[0]==34 && str[len-1]==34)
        return e_sucess;
    else
        return e_failure;
}
/*Checking it is a Identifier or not*/
int isIdentifier(const char* str)
{
    if(((strcmp("include",str))==0) || ((strcmp("stdio",str))==0) || strcmp("h",str)==0)
        return e_failure;
    
    int len = strlen(str);
    for(int i=0; i<len; i++)
    {
        if(!((str[i]>='a' && str[i]<='z')
            || (str[i]>='A' && str[i]<='Z')
            || (str[i]>='0' && str[i]<='9')
            || str[i]== '_'))
            return e_failure;
    }
    return e_sucess;
}

/*int isDirectory(const char* str)
{
    if(strstr(directry,str)!=NULL)
        return e_sucess;
    else
        return e_failure;
}*/