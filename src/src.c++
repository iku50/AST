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
using namespace std;
string token_text[99];
string tokenText;
int line = -1;
int get_token(_IO_FILE *fp)
{
    char c;
    static int p = 0;
    tokenText = "";
    while (c = fgetc(fp) == ' ' || c == '\n' || c == 0)
    {
        if (c == '\n')
            line++;
    }
    // TODO CHAR_CONST的情形未录入
    while (c = fgetc(fp) != ' ' && c != '\n' && c != '\0'){
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
    }
    return ERROR_TOKEN;
}
bool cifafenxi(_IO_FILE *outputfile, int i, string token)
{
    if (i == ERROR_TOKEN)
        return false;
    switch (i)
    {
    case IDENT:
        fprintf(outputfile, "标识符\t%s", tokenText);
        break;
    case FLOAT_CONST:
        fprintf(outputfile, "浮点数\t%s", tokenText);
        break;
    case INT_CONST:
        fprintf(outputfile, "整数\t%s", tokenText);
        break;
    default:
        fprintf(outputfile, "%s", tokenText);
        break;
    }
    return true;
}
void Start(int argc, char **argv)
{
    int ch;
    string fileName;
    string outFileName;
    printf("welcome to use this ast tool!\n");
    while ((ch = getopt(argc, argv, "f:o:")) != -1)
    {
        switch (ch)
        {
        case 'f':
            fileName = optarg;
            break;
        case 'o':
            outFileName = optarg;
            break;
            /*
            default:
                printf("Usage: ./main [-f file] [-o outfile]\n");
                exit(1);
            */
        }
    }
    fileName = "aaa.c";
    if (fileName == "")
    {
        fileName == "aaa.c";
        // printf("Usage: ./main [-f file] [-o outfile]\n");
        // exit(1);
    }
    if (outFileName == "")
    {
        outFileName = "ast" + fileName;
    }
    _IO_FILE *fp = fopen(fileName.c_str(), "r+");
    if (fp == NULL)
    {
        printf("open file error\n");
        exit(2);
    }
    _IO_FILE *fp2 = fopen(outFileName.c_str(), "w+");
    if (fp2 == NULL)
    {
        printf("open output file error\n");
        exit(2);
    }
    get_token(fp);
    get_token(fp);
    while (cifafenxi(fp2, get_token(fp), tokenText))
    {
        fprintf(fp2, "\n");
    };
    fclose(fp);
    fclose(fp2);
    printf("mission complete!\n");
}