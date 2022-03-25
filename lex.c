#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 1000
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5
#define NUM_INDENTIFIERS 10

lexeme *list;
int lex_index, char_index;
char reserved_words[NUM_INDENTIFIERS][MAX_IDENT_LEN] = {
    {"var"},
    {"procedure"},
    {"call"},
    {"begin"},
    {"end"},
    {"if"},
    {"do"},
    {"while"},
    {"read"},
    {"write"},
};

int alphatoken(char *input);
int numbertoken(char *input);
int symboltoken(char *input);
void comment(char *input);
int reservedcheck(char *buffer);
void printlexerror(int type);
void printtokens();

lexeme *lexanalyzer(char *input, int printFlag)
{
    list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);
    lex_index = 0;
    char_index = 0;

    while (input[char_index] != '\0')
    {
        if (isspace(input[char_index]))
        {
            char_index++;
            //continue;
        }
        else if (iscntrl(input[char_index]))
        {
            char_index++;
            //continue;
        }
        else if (isdigit(input[char_index]))
        {
            if(numbertoken(input)==-1)
            {
                return NULL;
            }
        }
        else if (isalpha(input[char_index]))
        {
            if(alphatoken(input)==-1)
            {
                return NULL;
            }
            
        }
        else
        {
            if(symboltoken(input)==-1)
            {
                return NULL;
            }
        }
    }

    if (printFlag)
        printtokens();
    list[lex_index++].type = -1;
    return list;
}

void printtokens()
{
    int i;
    printf("Lexeme Table:\n");
    printf("lexeme\t\ttoken type\n");
    for (i = 0; i < lex_index; i++)
    {
        switch (list[i].type)
        {
        case periodsym:
            printf("%11s\t%d", ".", periodsym);
            break;
        case varsym:
            printf("%11s\t%d", "var", varsym);
            break;
        case lbracketsym:
            printf("%11s\t%d", "[", lbracketsym);
            break;
        case procsym:
            printf("%11s\t%d", "procedure", procsym);
            break;
        case rbracketsym:
            printf("%11s\t%d", "]", rbracketsym);
            break;
        case callsym:
            printf("%11s\t%d", "call", callsym);
            break;
        case commasym:
            printf("%11s\t%d", ",", commasym);
            break;
        case beginsym:
            printf("%11s\t%d", "begin", beginsym);
            break;
        case semicolonsym:
            printf("%11s\t%d", ";", semicolonsym);
            break;
        case endsym:
            printf("%11s\t%d", "end", endsym);
            break;
        case assignsym:
            printf("%11s\t%d", ":=", assignsym);
            break;
        case ifsym:
            printf("%11s\t%d", "if", ifsym);
            break;
        case questionsym:
            printf("%11s\t%d", "?", questionsym);
            break;
        case dosym:
            printf("%11s\t%d", "do", dosym);
            break;
        case colonsym:
            printf("%11s\t%d", ":", colonsym);
            break;
        case readsym:
            printf("%11s\t%d", "read", readsym);
            break;
        case lparenthesissym:
            printf("%11s\t%d", "(", lparenthesissym);
            break;
        case writesym:
            printf("%11s\t%d", "write", writesym);
            break;
        case rparenthesissym:
            printf("%11s\t%d", ")", rparenthesissym);
            break;
        case identsym:
            printf("%11s\t%d", list[i].name, identsym);
            break;
        case eqlsym:
            printf("%11s\t%d", "==", eqlsym);
            break;
        case numbersym:
            printf("%11d\t%d", list[i].value, numbersym);
            break;
        case neqsym:
            printf("%11s\t%d", "<>", neqsym);
            break;
        case modsym:
            printf("%11s\t%d", "%", modsym);
            break;
        case lsssym:
            printf("%11s\t%d", "<", lsssym);
            break;
        case divsym:
            printf("%11s\t%d", "/", divsym);
            break;
        case leqsym:
            printf("%11s\t%d", "<=", leqsym);
            break;
        case multsym:
            printf("%11s\t%d", "*", multsym);
            break;
        case gtrsym:
            printf("%11s\t%d", ">", gtrsym);
            break;
        case subsym:
            printf("%11s\t%d", "-", subsym);
            break;
        case geqsym:
            printf("%11s\t%d", ">=", geqsym);
            break;
        case addsym:
            printf("%11s\t%d", "+", addsym);
            break;
        case whilesym:
            printf("%11s\t%d", "while", whilesym);
            break;
        default:
            printf("%11s\t%s", "err", "err");
            break;
        }
        printf("\n");
    }
    printf("\n");
}

void printlexerror(int type)
{
    if (type == 1)
        printf("Lexical Analyzer Error: Invalid Identifier\n");
    else if (type == 2)
        printf("Lexical Analyzer Error: Number Length\n");
    else if (type == 3)
        printf("Lexical Analyzer Error: Identifier Length\n");
    else if (type == 4)
        printf("Lexical Analyzer Error: Invalid Symbol\n");
    else
        printf("Implementation Error: Unrecognized Error Type\n");

    free(list);
    return;
}

int symboltoken(char *input)
{
    char curr_char = input[char_index];
    switch (curr_char)
    {
    case '.':
        list[lex_index++].type = periodsym;
        break;

    case '[':
        list[lex_index++].type = lbracketsym;
        break;

    case ']':
        list[lex_index++].type = rbracketsym;
        break;

    case ',':
        list[lex_index++].type = commasym;
        break;

    case ';':
        list[lex_index++].type = semicolonsym;
        break;

    case '?':
        list[lex_index++].type = questionsym;
        break;

    case ':':
        if (input[char_index + 1] == '=')
        {
            list[lex_index++].type = assignsym;
            char_index = char_index + 2;
            return 0;
        }
        else
        {
            list[lex_index++].type = colonsym;
        }
        break;

    case '(':
        list[lex_index++].type = lparenthesissym;
        break;

    case ')':
        list[lex_index++].type = rparenthesissym;
        break;

    case '=':
        if (input[char_index + 1] == '=')
        {
            list[lex_index++].type = eqlsym;
            char_index = char_index + 2;
            return 0;
        }
        else
        {
            printlexerror(4);
            return -1;
        }
        break;

    case '<':
        if (input[char_index + 1] == '>')
        {
            list[lex_index++].type = neqsym;
            char_index = char_index + 2;
            return 0;
        }
        else if (input[char_index + 1] == '=')
        {
            list[lex_index++].type = leqsym;
            char_index = char_index + 2;
            return 0;
        }
        else
        {
            list[lex_index++].type = lsssym;
        }
        break;

    case '>':
        if (input[char_index + 1] == '=')
        {
            list[lex_index++].type = geqsym;
            char_index = char_index + 2;
            return 0;
        }
        else
        {
            list[lex_index++].type = gtrsym;
        }
        break;

    case '+':
        list[lex_index++].type = addsym;
        break;

    case '-':
        list[lex_index++].type = subsym;
        break;

    case '*':
        list[lex_index++].type = multsym;
        break;

    case '/':
        if (input[char_index + 1] == '/')
        {
            char_index = char_index + 2;
            comment(input);
            return 0;
        }
        else
        {
            list[lex_index++].type = divsym;
        }
        break;

    case '%':
        list[lex_index++].type = modsym;
        break;

    default:
        printlexerror(4);
        return -1;
        break;
    }

    char_index++;

    return 0;
}

void comment(char *input)
{
    char curr_char = input[char_index];
    // Loop until new line or end of file
    while (curr_char != '\n' && curr_char != '\r' && curr_char != '\0')
    {
        char_index++;
        curr_char = input[char_index];
    }
    if(curr_char != '\0'){
    	char_index++;
	}
	return;
}

int alphatoken(char *input)
{
    //we know that the first char is alpha
    //so, simply place it into the buffer
    int index=0;
    char buffer[MAX_IDENT_LEN+1] = "";
    buffer[index] = input[char_index];

    //update pointers
    index++;
    char_index++;

    //get the next char
    char curr_char = input[char_index];

    //loop while we find alpha or digit characters
    //and while we have not exceeded the identifier length
    while ((isalpha(curr_char) || isdigit(curr_char)) && index < 11)
    {
        buffer[index] = curr_char;
        index++;
        char_index++;
        curr_char = input[char_index];
    }

    //check if the current char is digit or alpha and if it exceeded the length of the identifier
    //if yes, then print lex error for identifier length
    if((isalpha(curr_char) || isdigit(curr_char)) && index >= 11)
    {
        printlexerror(3);
        return -1;
    }

    //check if it is a reserved word
    if(reservedcheck(buffer)==0)
    {
        return 0;
    }

    //it is not a reserved word
    //so, store identifier
    list[lex_index].type = identsym;
    strcpy(list[lex_index++].name, buffer);

    return 0;
}

int reservedcheck(char *buffer)
{
    //loop through all possible reserved words
    //if it matches, assign the type and return 0
    //else, return -1
    for(int i=0; i<10; i++)
    {
        if(strcmp(buffer, reserved_words[i]) == 0)
        {
            if(i==0)
            {
                list[lex_index++].type = varsym;
            }
            else if(i==1)
            {
                list[lex_index++].type = procsym;
            }
            else if(i==2)
            {
                list[lex_index++].type = callsym;
            }
            else if(i==3)
            {
                list[lex_index++].type = beginsym;
            }
            else if(i==4)
            {
                list[lex_index++].type = endsym;
            }
            else if(i==5)
            {
                list[lex_index++].type = ifsym;
            }
            else if(i==6)
            {
                list[lex_index++].type = dosym;
            }
            else if(i==7)
            {
                list[lex_index++].type = whilesym;
            }
            else if(i==8)
            {
                list[lex_index++].type = readsym;
            }
            else if(i==9)
            {
                list[lex_index++].type = writesym;
            }
            return 0;
        }
    }

    return -1;
}

int numbertoken(char *input)
{
    //we know that the first char is a digit
    //so, simply place it into the buffer
    int index=0;
    char buffer[MAX_NUMBER_LEN+1]="";
    buffer[index] = input[char_index];

    //update pointers
    index++;
    char_index++;

    //get the next char
    char curr_char = input[char_index];

    //loop while we find digit characters
    //and while we have not exceeded the number length
    while (isdigit(curr_char) && index < 5)
    {
        buffer[index] = curr_char;
        index++;
        char_index++;
        curr_char = input[char_index];
    }

    //check if the current char is digit and if it exceeded the number length limit
    //if yes, then print lex error for number length
    if(isdigit(curr_char) && index >= 5)
    {
        printlexerror(2);
        return -1;
    }

    //check if the current char is alpha
    //if yes, then print lex error for invalid identifier
    if(isalpha(curr_char))
    {
        printlexerror(1);
        return -1;
    }

    //it is a valid number
    //so, store number
    int ans = atoi(buffer);
    list[lex_index].type = numbersym;
    list[lex_index++].value = ans;

    return 0;
    
}
