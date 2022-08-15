#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "src.h"
using namespace std;
enum ASTtype{
    PROGRAM,            //程序
    MARCOSEQ,           //程序头序列
    MARC,              //程序头
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
extern int tab;
void free0(ASTtree* k);

ASTtree *ASTtreeinit(ASTtree *k, int tt, int at, string ttt);
ASTtree *program(_IO_FILE *fp, string programname);
ASTtree *MarcoSeq(_IO_FILE *fp);
ASTtree *Marco(_IO_FILE *fp);
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
ASTtree *State(_IO_FILE *fp,bool iselse);
ASTtree *Exp(_IO_FILE *fp,token_kind endsym);
void PreTraver(_IO_FILE *outputfile, ASTtree *t);
void Formatter(_IO_FILE *outputfile, ASTtree *t);
void InorderTraver(_IO_FILE *fp, ASTtree *t);