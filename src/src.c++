/*
 * @Author: wizzz wizo.o@outlook.com
 * @Date: 2022-07-15 14:33:46
 * @LastEditors: wizzz wizo.o@outlook.com
 * @LastEditTime: 2022-07-16 19:04:15
 * @FilePath: /AST/def.h
 * @Description:
 *
 * Copyright (c) 2022 by wiz wizo.o@outlook.com, All Rights Reserved.
 */
#include "src.h"
int get_token(_IO_FILE *fp)
{
    char c;
    static int p = 0;
    tokenText = "";
    while (c = fgetc(fp) == ' ' || c == '\n')
    {
        if (c == '\n')
            line++;
    }
    //TODO CHAR_CONST的情形未录入
    if (isalpha(c))
    {
        do
        {
            tokenText += c;
        } while (isalpha(c = fgetc(fp)) || isdigit(c = fgetc(fp)));
        ungetc(c, fp);
        if (keyword.find(tokenText) != keyword.end())
        {
            return keyword[tokenText];
        }
        else
        {
            token_text[p++] = tokenText;
            return IDENT;
        }
    }
    else if (isdigit(c))
    {
        do
        {
            tokenText += c;
        } while (isdigit(c = fgetc(fp)));
        ungetc(c, fp);
        if (c = getc(fp) == '.')
        {
            do
            {
                tokenText += c;
            } while (isdigit(c = fgetc(fp)));
            ungetc(c, fp);
            if (c = getc(fp) != ' ' || c != '\n')
                return ERROR_TOKEN;
            else
            {
                token_text[p++] = tokenText;
                return FLOAT_CONST;
            }
        }
        else if (c == ' ' || c == '\n')
        {
            token_text[p++] = tokenText;
            return INT_CONST;
        }
        else
            return ERROR_TOKEN;
    }
    switch (c)
    {
    case '=':
        c = fgetc(fp);
        if (c == '=')
            return EQ;
        ungetc(c, fp);
        return ASSIGN;
    case '+':
        return ADD;
    case '-':
        return MINUS;
    case '*':
        return MULTI;
    case '#':
        return MARCO;
    case '/':
        return DIVIDE;
    case '%':
        return REMAIN;
    case '(':
        return LSP;
    case '[':
        return LMP;
    case '{':
        return LLP;
    case ')':
        return RSP;
    case ']':
        return RMP;
    case '}':
        return RLP;
    case ':':
        return COLON;
    case ';':
        return COMMA;
    case ',':
        return SEMI;
    case '\\':
        if (c = fgetc(fp) == '\\')
            return NOTES;
        ungetc(c, fp);
        return ERROR_TOKEN;
    case '&':
        if (c = fgetc(fp) == '&')
            return AND;
        ungetc(c, fp);
        return ERROR_TOKEN;
    case '|':
        if (c = fgetc(fp) == '|')
            return OR;
        ungetc(c, fp);
        return ERROR_TOKEN;
    default:
        if (feof(fp))
            return EOF;
        else
            return ERROR_TOKEN;
    }
    return ERROR_TOKEN;
}
bool cifafenxi(int i,string token){
    if(i==ERROR_TOKEN)return false;
    switch(i){
        case IDENT :
            printf("标识符\t%s",tokenText);
            break;
        case FLOAT_CONST :
            printf("浮点数\t%s",tokenText);
            break;
        case INT_CONST :
            printf("整数\t%s",tokenText);
            break;
    }
    return true;
}
void Start(int argc, char **argv){

}