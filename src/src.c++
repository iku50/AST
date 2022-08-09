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
#include "ASTgenerate.h"
string tokenText;
int line = -1;

token_kind get_token(_IO_FILE *fp)
{
    char c;
    string tokenText = "";
    while ((c = fgetc(fp)) == ' ' || c == '\n' || c == 0)
    {
        if (c == '\n')
            line++;
    }
    if (c == -1)
        return EOF;
    ungetc(c, fp);
    while ((c = fgetc(fp)) != ' ' && c != '\n' && c != '\0')
    {
        if (c == '"')
        {
            while ((c = fgetc(fp)) != '"')
            {
                tokenText += c;
                if (c == -1)
                    return EOF;
            }
            tokenText += c;
            token_text[p++] = tokenText;
            return CHAR_CONST;
        }
        if (isalpha(c))
        {
            do
            {
                tokenText += c;
                c = fgetc(fp);
            } while (isalpha(c) || isdigit(c) || c == '_');
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
            if ((c = getc(fp)) == '.')
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
                    ungetc(c, fp);
                    return FLOAT_CONST;
                }
            }
            else if (c == ' ' || c == '\n' || c == 0 || c == ',' || c == ';' || c == ')' || c == ']')
            {
                token_text[p++] = tokenText;
                ungetc(c, fp);
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
            if ((c = fgetc(fp) )== '+')
                return ADDS;
            ungetc(c, fp);
            return ADD;
        case '-':
            if ((c = fgetc(fp)) == '-')
                return MINUSS;
            ungetc(c, fp);
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
            return SEMI;
        case ',':
            return COMMA;
        case '\\':
            if ((c = fgetc(fp)) == '\\')
                return NOTES;
            ungetc(c, fp);
            return ERROR_TOKEN;
        case '&':
            if ((c = fgetc(fp)) == '&')
                return AND;
            ungetc(c, fp);
            return ERROR_TOKEN;
        case '|':
            if ((c = fgetc(fp)) == '|')
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
    if (i == EOF)
    {
        return false;
    }
    switch (i)
    {
    case IDENT:
        fprintf(outputfile, "标识符\t%s", token_text[p - 1].c_str());
        break;
    case FLOAT_CONST:
        fprintf(outputfile, "浮点数\t%s", token_text[p - 1].c_str());
        break;
    case INT_CONST:
        fprintf(outputfile, "整数\t%s", token_text[p - 1].c_str());
        break;
    case ADD:
        fprintf(outputfile, "加\t+");
        break;
    case MINUS:
        fprintf(outputfile, "减\t-");
        break;
    case MULTI:
        fprintf(outputfile, "乘\t*");
        break;
    case DIVIDE:
        fprintf(outputfile, "除\t/");
        break;
    case REMAIN:
        fprintf(outputfile, "余\t%");
        break;
    case EQ:
        fprintf(outputfile, "等于\t==");
        break;
    case ASSIGN:
        fprintf(outputfile, "赋值\t=");
        break;
    case LSP:
        fprintf(outputfile, "左括号\t(");
        break;
    case RSP:
        fprintf(outputfile, "右括号\t)");
        break;
    case LMP:
        fprintf(outputfile, "左中括号\t[");
        break;
    case RMP:
        fprintf(outputfile, "右中括号\t]");
        break;
    case LLP:
        fprintf(outputfile, "左大括号\t{");
        break;
    case RLP:
        fprintf(outputfile, "右大括号\t}");
        break;
    case COLON:
        fprintf(outputfile, "冒号\t:");
        break;
    case COMMA:
        fprintf(outputfile, "逗号\t,");
        break;
    case SEMI:
        fprintf(outputfile, "分号\t;");
        break;
    case NOTES:
        fprintf(outputfile, "注释\t\\");
        break;
    case AND:
        fprintf(outputfile, "与\t&");
        break;
    case OR:
        fprintf(outputfile, "或\t|");
        break;
    case ERROR_TOKEN:
        fprintf(outputfile, "错误\t%s");
        break;
    case EOF:
        fprintf(outputfile, "结束\tEOF");
        break;
    case MARCO:
        fprintf(outputfile, "宏\t#");
        break;
    case INT:
        fprintf(outputfile, "整型\tint");
        break;
    case FLOAT:
        fprintf(outputfile, "浮点型\tfloat");
        break;
    case CHAR:
        fprintf(outputfile, "字符型\tchar");
        break;
    case VOID:
        fprintf(outputfile, "void\tvoid");
        break;
    case IF:
        fprintf(outputfile, "if\tif");
        break;
    case ELSE:
        fprintf(outputfile, "else\telse");
        break;
    case WHILE:
        fprintf(outputfile, "while\twhile");
        break;
    case RETURN:
        fprintf(outputfile, "return\treturn");
        break;
    default:
        fprintf(outputfile, "error");
        break;
    }
    return true;
}

void yufafenxi(_IO_FILE *fp, string filename,_IO_FILE *outputfile)
{
    ASTtree *root = program(fp, filename);
    
    if(root == NULL)
    {
        printf("......ASTtree building failed......\n");
        return;
    }else{
        PreTraver(outputfile,root);
    }
}

void printtab(int n, _IO_FILE *outputfile)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(outputfile, "\t");
    }
}

int precede(token_kind a, token_kind b)
{
    switch (a)
    {
    case ADD:
    case MINUS:
        if (b == RSP || b == ADD || b == MINUS || b == MULTI || b == DIVIDE || b == REMAIN)
            return 1;
        else
            return 0;
        break;
    case MULTI:
    case DIVIDE:
    case REMAIN:
        if (b == RSP || b == MULTI || b == DIVIDE || b == REMAIN)
            return 1;
        else
            return 0;
        break;
    case LSP:
        if (b == RSP)
            return 1;
        else
            return 0;
        break;
    case RSP:
        if (b == LSP)
            return -1;
        else if (b == RSP || b == ASSIGN || b == BG)
            return -2;
        else
            return 1;
        break;
    case ASSIGN:
        if (b == ASSIGN || b == BG)
            return 0;
        else
            return -2;
        break;
    case EQ:
    case NEQ:
        if (b == ASSIGN || b == BG)
            return 0;
        else
            return 1;
        break;
    case LEQ:
    case MEQ:
    case MORE:
    case LESS:
        if (b == ASSIGN || b == EQ || b == NEQ || b == BG)
            return 0;
        else
            return 1;
        break;
    case BG:
        if (b == BG)
            return -1;
        else
            return 1;
        break;
    default:
        return -2;
        break;
    }
}

bool JudgeIdentConst(token_kind Ident, token_kind Const)
{
    switch (IDENT)
    {
    case INT:
        if (Const == INT_CONST)
            return true;
        break;
    case FLOAT:
        if (Const == FLOAT_CONST)
            return true;
        break;
    case CHAR:
        if (Const == CHAR_CONST)
            return true;
        break;
    }
    return false;
}

void Start(int argc, char **argv)
{
    int ch;
    string fileName;
    string outFileName;
    printf("welcome to use this ast tool!\n");
    printf("please input the file name you want to analyse:\n");
    printf("input -h to check more information\n");
    getchar();
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
        case 'h':
            printf("this is a ast tool, you can use it to analyse the ast of a c program\n");
            printf("this program is a student project of c language\n");
            printf("-f:input file name\n");
            printf("-o:output file name\n");
            break;
        default:
            printf("Usage: ./main [-f file] [-o outfile]\n");
            exit(1);
        }
    }
    //fileName = "test.c";
    if (fileName == "")
    {
        printf("Usage: ./main [-f file] [-o outfile]\n");
        exit(1);
    }
    if (outFileName == "")
    {
        outFileName = "output/" + fileName + ".txt";
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
    yufafenxi(fp, fileName,fp2);
    fclose(fp);
    fclose(fp2);
    printf("mission complete!\n");
}