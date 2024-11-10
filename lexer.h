#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 27
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    INTEGRAL_CONSTANT,
    Floating_CONSTANT,
    HEXA_CONSTANT,
    OCTAL_CONSTANT,
    DIRECTORY,
    UNKNOWN
} TokenType;

typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

typedef enum {
    e_sucess,
    e_failure
}Validate;

Validate initializeLexer(const char* filename);
Validate getNextToken();
void categorizeToken(Token* token);
int isKeyword(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(char *ch);
int isConstant(const char* str);
int isIdentifier(const char* str);
//int isDirectory(const char* str);

#endif
