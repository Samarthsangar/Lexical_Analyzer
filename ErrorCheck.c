/*Error check C file*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ErrorCheck.h"
#include "lexer.h"

/*Extern connect variable's*/
extern FILE *fptr;
extern Token token;
extern char file[MAX_KEYWORDS];
int Error_flag=0;

/*Checking error*/
Validat ErrorCheck()
{
    /*Clearing the buffer*/
    memset(token.lexeme,0,MAX_TOKEN_SIZE);
    char *ch=calloc(1,1);

    label5 :
    fscanf(fptr,"%c",ch);

    if(strchr(ch,'}')!=NULL)
        return e_failur;

    if(ch[0]!='\n')
    {
        strcat(token.lexeme,ch);
        goto label5;
    }
    /*Checking error in header*/
    if(isHeader(token.lexeme)==e_sucesss)
        return e_sucesss;
    
    /*Checking error in printf*/
    else if(isPrintf(token.lexeme)==e_sucesss)
        return e_sucesss;
    
    /*Checking error in int*/
    else if(isInt(token.lexeme)==e_sucesss)
        return e_sucesss;
    
    /*Checking error in float*/
    else if(isFloat(token.lexeme)==e_sucesss)
        return e_sucesss;
    
    else if(strlen(token.lexeme)==6 && (strchr(token.lexeme,44)!=NULL || strchr(token.lexeme,39)!=NULL || strchr(token.lexeme,34)!=NULL || strchr(token.lexeme,123)!=NULL || strchr(token.lexeme,40)!=NULL))
    {   
        printf("%s :\nError : error: missing terminating character\n\t%s\n\n",file,token.lexeme);
        Error_flag=1;
        return e_sucesss;
    }
    /*Else return Not error*/ 
    else
        return e_sucesss;
}

/*Checking error in header or not*/
Validat isHeader(char arr[MAX_TOKEN_SIZE])
{
    int flag=1;
    if(!(arr[0]=='#' && (strstr(arr,".h")!=NULL || strstr(arr,"include")!=NULL)))
            return e_failur;

    if((strstr(arr,"include")!=NULL) && (strstr(arr,".h")!=NULL) && (strchr(arr,'<')!=NULL) && (strchr(arr,'>')!=NULL))
    {
            flag=0;
    }
    if(flag==1)
    {
        printf("%s :\nError : Header file Error\n\t%s\n\n",file,arr);
        Error_flag=1;
    }
    return e_sucesss;
}

/*Checking error in printf or not*/
Validat isPrintf(char arr[MAX_TOKEN_SIZE])
{
    int flag=0;
    if(!((strchr(arr,'(')!=NULL || strchr(arr,')')!=NULL) && (strstr(arr,"printf")!=NULL)))
            return e_failur;

    if((strstr(arr,"printf")!=NULL) && (strchr(arr,';')!=NULL) && (strchr(arr,'(')!=NULL) && (strchr(arr,')')!=NULL))
    {
            flag++;
    }
    int set=0;
    for(int i=0; arr[i]!=0; i++)
    {
        if(arr[i]==34)
            set++;
    }
    if(set==2)
        flag++;
    if(flag!=2)
    {
        printf("%s :\nError : printf Keyword Error\n\t%s\n\n",file,arr);
        Error_flag=1;
    }
    return e_sucesss;
}
/*Checking error in int or not*/
Validat isInt(char arr[MAX_TOKEN_SIZE])
{
    int flag=0,falg1=1;
    if(((strchr(arr,'=')==NULL) && (strstr(arr,"int")!=NULL) && (strstr(arr,"main")==NULL)))
    {
        falg1=0;
        goto label6;
    }

    if(!((strchr(arr,'=')!=NULL) && (strstr(arr,"int")!=NULL)))
            return e_failur;

    for(int i=0; arr[i]!=0; i++)
        {
            if(arr[i]==32)
            {
                if(arr[i+1]>='0' && arr[i+1]<='9' && arr[i-1]!='=')
                    flag++;
            }
            else if((strchr(arr,';'))==NULL || (strchr(arr,'"'))!=NULL)
            {
                flag++;
                break;
            }
        }
    if((strchr(arr,';')!=NULL))
    {
            if((strchr(arr,'(')!=NULL))
            {
                if((strchr(arr,')')!=NULL))
                    flag=0;
                else
                    flag++;
            }
    }
    else
        flag++;
    int set=0;
    if(strstr(arr,"0x")!=NULL || strstr(arr,"0X")!=NULL)
        set=1;
    else if(strstr(arr,"=0")!=NULL || strstr(arr,"= 0")!=NULL)
        set=2;
    char *ptr=strchr(arr,'=');
    int chcek=0;
   
    if(set==1)
    {
        for(int i=0; ptr[i]!=';'; i++)
        {
            if(ptr[i]=='=' || (ptr[i]=='x' || ptr[i]=='X'))
            {
                chcek++;
                continue;
            }
            else if(chcek>2)
            {
                set=5;
                break;
            }
            else if(ptr[i]==32)
                continue;

            if(!(((ptr[i]>='a' && ptr[i]<='f') || (ptr[i]>='A' && ptr[i]<='F')) || (ptr[i]>='0' && ptr[i]<='9')))
            {
                set=5;
                break;
            }
            else if(ptr[i]==';' && (ptr[i+1]!=32 || ptr[i+1]!='\n'))
            {
                set=5;
                break;
            }
            else if(ptr[i]==34)
            {
                set=5;
                break;
            }
        }
        if(set==5)
        {
            flag++;
        }
    }
    else 
    {
        
        for(int i=0; ptr[i]!=';'; i++)
        {
            if(ptr[i]=='=' || ptr[i]=='0' || ptr[i]==32)
                continue;

            if(((ptr[i]>='a' && ptr[i]<='z') || (ptr[i]>='A' && ptr[i]<='Z')))
            {
                set=5;
                break;
            }
            else if(ptr[i]==';' && (ptr[i+1]!=32 || ptr[i+1]!='\n'))
            {
                set=5;
                break;
            }
            else if(!(ptr[i]>='0' && ptr[i]<='7'))
            {
                set=5;
                break;
            }
            else if(ptr[i]==34)
            {
                set=5;
                break;
            }
        }
        if(set==5)
            flag++;
    }
    label6 :
    if(falg1==0)
    {
        for(int i=0; arr[i]!=0; i++)
        {
            if(arr[i]==32)
            {
                if(arr[i+1]>='0' && arr[i+1]<='9' && arr[i-1]!='=')
                    flag++;
            }
            else if((strchr(arr,';'))==NULL || (strchr(arr,'"'))!=NULL)
            {
                flag++;
                break;
            }
        }
    }
    if(flag!=0)
    {
        printf("%s :\nError : error: invalid suffix or digit on integer constant\n\t%s\n\n",file,arr);
        Error_flag=1;
    }
    return e_sucesss;
}
/*Checking error in float or not*/
Validat isFloat(char arr[MAX_TOKEN_SIZE])
{
    int flag=0,falg1=1;
    if(((strchr(arr,'=')==NULL) && (strstr(arr,"float")!=NULL) && (strstr(arr,"main")==NULL)))
    {
        falg1=0;
        goto label6;
    }

    if(!((strchr(arr,'=')!=NULL) && (strstr(arr,"float")!=NULL)))
            return e_failur;

    for(int i=0; arr[i]!=0; i++)
        {
            if(arr[i]==32)
            {
                if(arr[i+1]>='0' && arr[i+1]<='9' && arr[i-1]!='=')
                    flag++;
            }
            else if((strchr(arr,';'))==NULL || (strchr(arr,'"'))!=NULL)
            {
                flag++;
                break;
            }
        }
    if((strchr(arr,';')!=NULL))
    {
            if((strchr(arr,'(')!=NULL))
            {
                if((strchr(arr,')')!=NULL))
                    flag=0;
                else
                    flag++;
            }
    }
    else
        flag++;

    if(strstr(arr,"0x")!=NULL || strstr(arr,"0X")!=NULL)
        flag++;

    char *ptr=strchr(arr,'=');
    int chcek=0;
    int set=1;
    if(set==1)
    {
        for(int i=0; ptr[i]!=';'; i++)
        {
            if(ptr[i]=='=' || (ptr[i]=='.'))
            {
                chcek++;
                continue;
            }
            else if(chcek>2)
            {
                set=5;
                break;
            }
            else if(ptr[i]==32)
                continue;
            
            if(ptr[i]=='f' || ptr[i]=='F')
                continue;
            else if(((ptr[i]>='a' && ptr[i]<='z') || (ptr[i]>='A' && ptr[i]<='Z')))
            {
                set=5;
                break;
            }
            else if(ptr[i]==';' && (ptr[i+1]!=32 || ptr[i+1]!='\n'))
            {
                set=5;
                break;
            }
            else if(ptr[i]==34)
            {
                set=5;
                break;
            }
        }
        if(set==5)
        {
            flag++;
        }
    }
    
    label6 :
    if(falg1==0)
    {
        for(int i=0; arr[i]!=0; i++)
        {
            if(arr[i]==32)
            {
                if(arr[i+1]>='0' && arr[i+1]<='9' && arr[i-1]!='=')
                    flag++;
            }
            else if((strchr(arr,';'))==NULL || (strchr(arr,'"'))!=NULL)
            {
                flag++;
                break;
            }
        }
    }
    if(flag!=0)
    {
        printf("%s :\nError : error: invalid suffix or digit on Floating constant\n\t%s\n\n",file,arr);
        Error_flag=1;
    }
    return e_sucesss;
}