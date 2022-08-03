#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <unordered_map>
#include <stdlib.h>
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
    RETURN,             //return
    WHILE,              //while
    FOR,                //for
    BREAK,              //break
    CONTINUE,           //continue
    CASE,               //case
    ADD,                //+
    MINUS,              //-
    MULTI,              //*
    DIVIDE,             ///
    REMAIN,             //%
    MORE,               //>
    LESS,               //<
    MEQ,                //>=
    LEQ,                //<=
    EQ,                 //==
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
};

unordered_map<string, token_kind> keyword = {
    {"void",VOID},{"if", IF}, {"else", ELSE}, {"while", WHILE}, {"return", RETURN}, {"for", FOR}, {"break", BREAK}, {"continue", CONTINUE}, {"case", CASE}, {"int", INT}, {"char", CHAR}, {"float", FLOAT}, {"CONST", CONST}};
#include <string>
#include <fstream>
using namespace std;
enum ASTtype{
    PROGRAM,            //程序
    OUTDEFSEQ,          //外部定义序列
    OUTDEF,             //外部定义
    OUTVARDEF,          //外部变量定义
    TYPEEXP,            //类型说明符
    VARSEQ,             //变量序列
    VAR,                //变量
    FUNDEF,             //函数定义
    FORPARSEQ,          //参数序列
    FORPARS,            //参数
    COMSTATE,           //语句块
    LOCALVARSEQ,        //局部变量定义序列
    LOCALVARS,          //局部变量定义
    STATESEQ,           //语句序列
    STATES,             //语句
    EXP,                //表达式
    ARG,                //参数表达式
};
typedef struct ASTtree{
    int tokentype;
    int ASTtype;
    char* tokentext;
    struct ASTtree *lchild;
    struct ASTtree *rchild;
} ASTtree;
ASTtree *program(_IO_FILE *fp, string programname);
ASTtree *OutDefSeq(_IO_FILE *fp);
ASTtree *OutDef(_IO_FILE *fp);
ASTtree *OutVarDef(_IO_FILE *fp,token_kind type);
ASTtree *FunDef(_IO_FILE *fp);
token_kind get_token(_IO_FILE *fp);
bool cifafenxi(_IO_FILE* outputfile,int i,string token);
void Start(int argc,char **argv);
