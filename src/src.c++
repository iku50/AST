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
string token_text[99];
string tokenText;
int line = -1;
ASTtree *root;
int p = 0;
token_kind token_type = NU;
void free0(ASTtree *k)
{
    if (k == NULL)
        return;
    free0(k->fchild);
    free0(k->schild);
    free(k);
}

// tokentype->tt,ASTtype->at,tokentext->ttt
ASTtree *ASTtreeinit(ASTtree *k, int tt, int at, string ttt)
{
    k = (ASTtree *)malloc(sizeof(ASTtree));
    k->tokentype = tt;
    char *m = (char *)ttt.c_str();
    k->tokentext = (char *)malloc(sizeof(char) * 10);
    strcpy(k->tokentext, m);
    k->tokentype = tt;
    k->ASTtype = at;
    return k;
}

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
            else if (c == ' ' || c == '\n' || c == 0)
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
            return SEMI;
        case ',':
            return COMMA;
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

void yufafenxi(_IO_FILE *fp, string filename)
{
    program(fp, filename);
}

ASTtree *program(_IO_FILE *fp, string programname)
{
    token_type = get_token(fp);
    ASTtree *i = NULL;
    if ((i = OutDefSeq(fp)) != NULL)
    {
        ASTtree *root;
        root = ASTtreeinit(root, NU, PROGRAM, programname);
        root->fchild = i;
        root->schild = nullptr;
        return root;
    }
    else
    {
        cout << "error:there is no outsidedefine" << endl;
        return NULL;
    }
}

ASTtree *OutDefSeq(_IO_FILE *fp)
{
    if (token_type == EOF)
        return NULL;
    ASTtree *t;
    t = ASTtreeinit(t, NU, OUTDEFSEQ, "");
    t->fchild = OutDef(fp);
    t->schild = OutDefSeq(fp);
    token_type = get_token(fp);
    return t;
}

ASTtree *OutDef(_IO_FILE *fp)
{
    if (token_type != INT && token_type != FLOAT && token_type != CHAR && token_type != VOID)
    {
        cout << "error:outsidedefine is illegal" << endl;
        return NULL;
    }
    else
    {
        token_kind y = token_type;
        token_type = get_token(fp);
        if (token_type == IDENT)
        {
            ASTtree *t;
            t = ASTtreeinit(t, NU, OUTDEF, "");
            token_type = get_token(fp);
            if (token_type != LSP)
            {
                if (y == VOID)
                {
                    free0(t);
                    cout << "error:can't use void to describe a variable" << endl;
                    return NULL;
                }
                else
                {
                    t = OutVarDef(fp, y);
                    return t;
                }
            }
            else
                t = FunDef(fp, y);
            return t;
        }
        else
        {
            cout << "error: ident is illegal" << endl;
            return NULL;
        }
    }
}

ASTtree *FunDef(_IO_FILE *fp, token_kind type)
{
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, FUNDEF, token_text[p - 1]);
    t->fchild = ASTtreeinit(t->fchild, type, TYPEEXP, "");
    token_type = get_token(fp);
    if (token_type != RSP)
    {
        ASTtree *h = (ASTtree *)malloc(sizeof(ASTtree));
        h = ASTtreeinit(t, NU, FORPARSEQR, "");
        t->schild = h;
        h->fchild = ForParSeq(fp);
    }
    token_type = get_token(fp);
    if (token_type == SEMI)
    {
        token_type = get_token(fp);
        return t;
    }
    else if (token_type == LLP)
    {
        token_type = get_token(fp);//左大括号后面的第一个token
        t->tchild = Comstate(fp);
        token_type = get_token(fp);//右大括号后面的东西
        return t;
    }
    cout << "error:function body or declare is incomplete" << endl;
    exit(1);
}

ASTtree *Comstate(_IO_FILE *fp)
{
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, COMSTATE, "");
    if (token_type == RLP)
    {
        token_type = get_token(fp);
        return t;
    }
    else if (token_type == LLP)
    {
        t->schild=Comstate(fp);
    }
    else if (token_type == EOF)
    {
        cout << "error:comstate is incomplete" << endl;
        exit(1);
    }else{
        if(token_type==INT||token_type==FLOAT||token_type==CHAR)
            t->fchild=LocalVarSeq(fp);
        else t->fchild=NULL;
        //t->schild=StateSeq(fp);
    }
    token_type = get_token(fp);
    return t;
}

ASTtree *LocalVarSeq(_IO_FILE *fp)
{
    if (token_type == EOF){
        cout << "error:localvarseq is incomplete" << endl;
        return NULL;
    }
    if(token_type!=INT&&token_type!=FLOAT&&token_type!=CHAR){
        return NULL;
    }
    ASTtree *t;
    t = ASTtreeinit(t, NU, LOCALVARSEQ, "");
    t->fchild = LocalVars(fp);
    t->schild = LocalVarSeq(fp);
    token_type=get_token(fp);
    return t;
}

ASTtree *LocalVars(_IO_FILE *fp)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, LOCALVARS, "");
    t->fchild = ASTtreeinit(t->fchild, token_type, TYPEEXP, "");
    token_kind y = token_type;
    token_type = get_token(fp);//变量名
    token_type = get_token(fp);//变量名后符号
    t->schild=VarSeq(fp,y);
    return t;
}

ASTtree *ForParSeq(_IO_FILE *fp)
{
    if (token_type == COMMA)
        token_type = get_token(fp);
    if (token_type == RSP)
        return NULL;
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, FORPARSEQ, "");
    t->fchild = ForPars(fp);
    t->schild = ForParSeq(fp);
    return t;
}

ASTtree *ForPars(_IO_FILE *fp)
{
    if (token_type == RSP)
    {
        cout << "error:formal parameter is incomplete" << endl;
        exit(1);
    }
    else
    {
        ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
        t = ASTtreeinit(t, NU, FORPARS, "");
        t->fchild = ASTtreeinit(t->fchild, token_type, TYPEEXP, "");
        token_type = get_token(fp);
        t->schild = ASTtreeinit(t->schild, IDENT, VAR, token_text[p - 1]);
        token_type = get_token(fp);
        return t;
    }
}

ASTtree *VarSeq(_IO_FILE *fp,token_kind type){
    ASTtree *h;
    h = ASTtreeinit(h, NU, VARSEQ, "");
    h->fchild = ASTtreeinit(h->fchild, IDENT, VAR, token_text[p - 1]);
    while (1)
    {
        if(token_type==ASSIGN){
            token_type = get_token(fp);
            if(JudgeIdentConst(type,token_type)){
                token_type=get_token(fp);
            }else{
                cout <<"error:the assighment is illegal"<<endl;
                exit(1);
            }
        }
        switch (token_type)
        {
        case SEMI:
            token_type = get_token(fp);
            return h;
            break;
        case COMMA:
            token_type = get_token(fp);
            if (token_type != IDENT)
            {
                cout << "error" << endl;
                free0(h);
                return NULL;
            }
            ASTtree *q;
            q=ASTtreeinit(q, NU, VARSEQ, "");
            q->fchild = ASTtreeinit(q->fchild, IDENT, VAR, token_text[p - 1]);
            h->schild = q;
            h = q;
            token_type = get_token(fp);
            break;
        default:
            cout << "error" << endl;
            free0(h);
            return NULL;
            break;
        }
    }
}

bool JudgeIdentConst(token_kind Ident,token_kind Const){
    switch(IDENT){
        case INT:
            if(Const==INT_CONST) return true;
            break;
        case FLOAT:
            if(Const==FLOAT_CONST) return true;
            break;
        case CHAR:
            if(Const==CHAR_CONST) return true;
            break;
    }
    return false;
}

ASTtree *OutVarDef(_IO_FILE *fp, token_kind type)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, OUTVARDEF, "");
    t->fchild = ASTtreeinit(t->fchild, type, TYPEEXP, "");
    t->schild=VarSeq(fp,type);
    return t;
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
        default:
            printf("Usage: ./main [-f file] [-o outfile]\n");
            exit(1);
        }
    }
    fileName = "test.c";
    if (fileName == "")
    {
        printf("Usage: ./main [-f file] [-o outfile]\n");
        exit(1);
    }
    if (outFileName == "")
    {
        outFileName = "ast" + fileName + ".txt";
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
    yufafenxi(fp, fileName);
    fclose(fp);
    fclose(fp2);
    printf("mission complete!\n");
}