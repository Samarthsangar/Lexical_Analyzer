/***********************************************************LEXICAL ANALYZER******************************************************************** */
/*
Name : Samarth Rajendra Sangar
Date : 08/11/2024
Project Name : Lexical Analyzer
               Lexical Analyzer is the very first phase of compiler designing. It help you to covert sequence of character's into sequence
               token's 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "ErrorCheck.h"

/*File pointer*/
FILE *fptr;

/*structure variable*/
Token token;
char file[MAX_KEYWORDS];
extern int Error_flag;

extern const char* operators;
extern const char* specialCharacters;

/*Main function*/
int main(int argc, char *argv[]) {
    /*Chceking command line argument's & file extension*/
    if(argc!=2)
    {
        printf("Error : To many argument's in command line\n");
        printf("FORMATE -- > ./a.out <file.c>\n");
        return e_failure;
    }
    else if(strstr(argv[1],".c")==NULL)
    {
        printf("Error : Only \".c\" file provide (File error).\n");
        printf("FORMATE -- > ./a.out <file.c>\n");
        return e_failure;
    }
    /*Function call to Initial analyzer*/
    else if(initializeLexer(argv[1])==e_failure)
    { 
        printf("Open\t:%s: Failure\n",argv[1]);
        return e_failure;
    }
    /*Parsing file error*/
    strcpy(file,argv[1]);
     while (1) {
        if(ErrorCheck()!=e_sucess)             //function to check error's
            break;
    }
    if(Error_flag!=0)
        exit(0);
    
    /*Rewind the file*/
    rewind(fptr);

    /*Getting one one token's*/
    while (1) {
        if(getNextToken()!=e_sucess)
            break;
    }

    printf("\n\nFile Parsing\t: %s : Done\n",argv[1]);
    return e_sucess;
}

/*Called function for initializer*/
Validate initializeLexer(const char* filename)
{
    fptr=fopen(filename,"r");

    if(fptr==NULL)
        return e_failure;
    else
        printf("Open file\t\t: %s : Success\n",filename);
    
    printf("File comment remove\t: %s : Started\n",filename);
    FILE *fptr1=fopen("temp.c","w");
    char ch;
    int flag11=0;
    /*Removing first header*/
    while((ch=fgetc(fptr))!='\n')
    {
        if(ch==35 && flag11==0)
        {
            flag11=1;
        }
        if(flag11==0)
            goto label9;
    }

    /*Copying data to temp file*/
    while((ch=fgetc(fptr))!= EOF)
    {
        label9:
        if(ch==47)
        {
            if((ch=fgetc(fptr))==47)
            {
                while((ch=fgetc(fptr))!= '\n');
                continue;
            }
            else
            {
                fseek(fptr,-2,SEEK_CUR);
                ch=fgetc(fptr);
            }
        }
        if(ch==47)
        {
            if((ch=fgetc(fptr))==42)
            {
                lable4 :
                while((ch=fgetc(fptr))!=42);
                if((ch=fgetc(fptr))==47)
                {
                    fseek(fptr,1,SEEK_CUR);
                    continue;
                }
                else
                    goto lable4;
            }
            else
            {
                fseek(fptr,-2,SEEK_CUR);
                ch=fgetc(fptr);
            }
        }
        fputc(ch,fptr1);
    }
    printf("File comment remove\t: %s : Done\n",filename);
    fclose(fptr);
    fclose(fptr1);

    fptr=fopen("temp.c","r");
    if(fptr==NULL)
        return e_failure;
    else
    {
        printf("Parsing file\t\t: %s : Started\n\n",filename);
        return e_sucess;
    }
}

/*Getting 1-1 token's*/
Validate getNextToken()
{
    /*Making empty buffer*/
    memset(token.lexeme,0,MAX_TOKEN_SIZE);
    /*Allocation of memory*/
    char *ch=calloc(1,1);
    char *ch1=calloc(1,1);
    int len=0,flag=0;

    /*Cheking some condition's*/
    label2 :

    if(fscanf(fptr,"%c",ch1)<0)
        return e_failure;

    strcat(token.lexeme,ch1);
    
    if((token.lexeme[0]==32 || token.lexeme[0]==10))
        goto label3;

    len = strlen(token.lexeme);

    if(((token.lexeme[len-1]>='a' && token.lexeme[len-1]<='z') || (token.lexeme[len-1]>='A' && token.lexeme[len-1]<='Z') ||
        (token.lexeme[len-1]>='0' && token.lexeme[len-1]<='9') || token.lexeme[len-1]>='.')
        && (!((strchr(operators,token.lexeme[len-1])!=NULL)|| strchr(specialCharacters,token.lexeme[len-1])!=NULL))
        && (token.lexeme[len-1]!=32))
    {
        flag=1;
        goto label2;
    }
    else if(token.lexeme[len-1]!=32 && flag==1)
    {
        flag=0;
        token.lexeme[len-1]=0;
        fseek(fptr,-1,SEEK_CUR);
    }
    else if(token.lexeme[len-1]==32)
        token.lexeme[len-1]=0;

    label :
    len=strlen(token.lexeme);

    if((token.lexeme[0]==34) && (len==1 || token.lexeme[len-1]!=34))
    {
        fscanf(fptr,"%c",ch);
        strcat(token.lexeme,ch);
        goto label;
    }
    else if((token.lexeme[0]>='0' && token.lexeme[0]<='9'))
    {
        if(strstr(token.lexeme,".")!=NULL)
        {
            token.type=Floating_CONSTANT;
            goto label1;
        }
        else if(strstr(token.lexeme,"X")!=NULL || strstr(token.lexeme,"x")!=NULL)
        {
            token.type=HEXA_CONSTANT;
            goto label1;
        }
        else if(token.lexeme[0]=='0')
        {
            token.type=OCTAL_CONSTANT;
            goto label1;
        }
        token.type=INTEGRAL_CONSTANT;
        goto label1;
    }
    /*else if((strstr(token.lexeme,"x")!=NULL || strstr(token.lexeme,"X")!=NULL) && strlen(token.lexeme)!=1)
    {
        for(int i=1; token.lexeme[i]!=0; i++)
        {
            if(!(((token.lexeme[i]>='a' && token.lexeme[i]<='f') || (token.lexeme[i]>='A' && token.lexeme[i]<='F')) || (token.lexeme[i]>='0' && token.lexeme[i]<='9')))
            {
                goto label7;
            }
        }
        token.type=INTEGRAL_CONSTANT;
        goto label1;
    }*/
    else if(token.lexeme[len-1]==32)
        token.lexeme[len-1]=0;
    label7 :

    categorizeToken(&token);
    
    label1 :
    /*Printing the one one token information*/
    if(token.type != UNKNOWN)
    {
        int tem=token.type;

        char *ch3=tem==0?"Keyword":tem==1?"Operator":tem==2?"Special char":tem==3?"Literal":tem==4?"Identifier":tem==5?"Integral_const":tem==6?"Floating_const":tem==7?"Hexa_const":tem==8?"Octal_const":"directory";
        printf("%-15.15s : %s\n",ch3,token.lexeme);
    }
    label3 :
    memset(token.lexeme,0,MAX_TOKEN_SIZE);
    return e_sucess;
}