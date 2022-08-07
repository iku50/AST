#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <unordered_map>
#include <tuple>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <stack>
#undef EOF // 定义EOF为一个宏，避免冲突
using namespace std;
enum token_kind
{
    EOF,                //eof
    NU,                 //null
    ERROR_TOKEN,        //wrong token
    IDENT,              //identifier
    INT_CONST,          //integer constant
    FLOAT_CONST,        //float constant
    CHAR_CONST,         //char constant
    INT,                //int
    FLOAT,              //float
    CHAR,               //char
    VOID,               //void
    CONST,              //const
    IF,                 //if
    ELSE,               //else
    IFELSE,
    RETURN,             //return
    WHILE,              //while
    FOR,                //for
    BREAK,              //break
    CONTINUE,           //continue
    CASE,               //case
    ADD,                //+
    ADDS,               //++
    MINUS,              //-
    MINUSS,             //--
    MULTI,              //*
    DIVIDE,             ///
    REMAIN,             //%
    MORE,               //>
    LESS,               //<
    MEQ,                //>=
    LEQ,                //<=
    EQ,                 //==
    NEQ,                //!=
    ASSIGN,             //=
    AND,                //&&
    OR,                 //||
    LSP,                //(
    RSP,                //)
    LMP,                //[
    RMP,                //]
    LLP,                //{
    RLP,                //}
    SEMI,               //;
    COMMA,              //,
    COLON,              //:
    MARCO,              //#
    NOTES,              //注释
    BG,                 //开始结束标记
};

unordered_map<string, token_kind> keyword = {
    {"void",VOID},
    {"if", IF}, 
    {"else", ELSE}, 
    {"while", WHILE}, 
    {"return", RETURN}, 
    {"for", FOR}, 
    {"break", BREAK}, 
    {"continue", CONTINUE}, 
    {"case", CASE}, 
    {"int", INT}, 
    {"char", CHAR}, 
    {"float", FLOAT}, 
    {"CONST", CONST},
};


enum ASTtype{
    PROGRAM,            //程序
    OUTDEFSEQ,          //外部定义序列
    OUTDEF,             //外部定义
    OUTVARDEF,          //外部变量定义
    TYPEEXP,            //类型说明符
    VARSEQ,             //变量序列
    VAR,                //变量
    FUNDEF,             //函数定义
    FORPARSEQR,         //参数定义序列根
    FORPARSEQ,          //参数序列
    FORPARS,            //参数
    COMSTATE,           //语句块
    LOCALVARSEQ,        //局部变量定义序列
    LOCALVARS,          //局部变量定义
    STATESEQ,           //语句序列
    STATES,             //语句
    EXP,                //表达式
    ARG,                //参数表达式
    BINARY,             //二元表达式
};
typedef struct ASTtree{
    int tokentype;
    int ASTtype;
    char* tokentext;
    struct ASTtree *fchild;
    struct ASTtree *schild;
    struct ASTtree *tchild;
} ASTtree;
ASTtree *program(_IO_FILE *fp, string programname);
ASTtree *OutDefSeq(_IO_FILE *fp);
ASTtree *OutDef(_IO_FILE *fp);
ASTtree *OutVarDef(_IO_FILE *fp,token_kind type);
ASTtree *FunDef(_IO_FILE *fp,token_kind type);
ASTtree *ForParSeq(_IO_FILE *fp);
ASTtree *ForPars(_IO_FILE *fp);
ASTtree *VarSeq(_IO_FILE *fp,token_kind type);
ASTtree *Comstate(_IO_FILE *fp);
ASTtree *LocalVarSeq(_IO_FILE *fp);
ASTtree *LocalVars(_IO_FILE *fp);
ASTtree *StateSeq(_IO_FILE * fp);
ASTtree *State(_IO_FILE *fp);
ASTtree *Exp(_IO_FILE *fp,token_kind endsym);
int precede(token_kind a, token_kind b);
token_kind get_token(_IO_FILE *fp);
bool cifafenxi(_IO_FILE* outputfile,int i,string token);
bool JudgeIdentConst(token_kind Ident,token_kind Const);
void Start(int argc,char **argv);
