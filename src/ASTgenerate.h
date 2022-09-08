/*
 * @Author: iku50 wizo.o@outlook.com
 * @Date: 2022-08-08 17:55:38
 * @LastEditors: iku50 wizo.o@outlook.com
 * @LastEditTime: 2022-09-08 19:12:57
 * @FilePath: /我的坚果云/AST/src/ASTgenerate.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#include "src.h"

/*
	选定C语言的一个子集，要求包含：
（1）基本数据类型的变量、常量，以及数组。不包含指针、结构，枚举等。(完成)
（2) 双目算术运算符（+-* /%），关系运算符、逻辑与（&&）、逻辑或（||）、赋值运算符。不包含逗号运算符、位运算符、各种单目运算符等等。（完成）
（3）函数定义、声明与调用。（完成定义声明）
（4）表达式语句、复合语句、if语句的2种形式、while语句、for语句，return语句、break语句、continue语句、外部变量说明语句、局部变量说明语句。（完成）
（5）编译预处理（宏定义，文件包含）（完成文件包含）
（6）注释（块注释与行注释）（完成）
*/
using namespace std;
enum ASTtype{
    PROGRAM,            //程序
    MARCOSEQ,           //程序头序列
    MARC,               //程序头
    OUTDEFSEQ,          //外部定义序列
    OUTDEF,             //外部定义
    OUTVARDEF,          //外部变量定义
    TYPEEXP,            //类型说明符
    VARSEQ,             //变量序列
    VAR,                //变量
    FORGR,              //for语法
    FUNDEF,             //函数定义
    FUNUSE,             //函数使用
    FORPARSEQR,         //参数定义序列根
    FORPARSEQ,          //参数序列
    FORPARS,            //参数
    PAR,                //实参
    COMSTATE,           //语句块
    LOCALVARSEQ,        //局部变量定义序列
    LOCALVARS,          //局部变量定义
    STATESEQ,           //语句序列
    STATES,             //语句
    EXP,                //表达式
    BINARY,             //二元表达式
    NOTESEQ,            //注释序列
    NOTE,               //注释
    NOTEP,              //注释块
};
//ASTtree的数据结构
typedef struct ASTtree{
    int tokentype;
    int ASTtype;
    char* tokentext;
    struct ASTtree *fchild;
    struct ASTtree *schild;
    struct ASTtree *tchild;
} ASTtree;
typedef struct fun{
    char* name;
    int par;
}fun;
extern int tab;
bool istab=true;
extern fun func[20];
int canbreak=true;
void free0(ASTtree* k);
ASTtree *ASTtreeinit(ASTtree *k, int tt, int at, string ttt);
ASTtree *program(_IO_FILE *fp, string programname);
ASTtree *MarcoSeq(_IO_FILE *fp);
ASTtree *Marco(_IO_FILE *fp);
ASTtree *OutDefSeq(_IO_FILE *fp);
ASTtree *OutDef(_IO_FILE *fp);
ASTtree *OutVarDef(_IO_FILE *fp,token_kind type);
ASTtree *FunDef(_IO_FILE *fp,token_kind type);
ASTtree *FunUse(_IO_FILE *fp,int funnum);
ASTtree *ForParSeq(_IO_FILE *fp,bool isde);
ASTtree *ForPars(_IO_FILE *fp);
ASTtree *VarSeq(_IO_FILE *fp,token_kind type);
ASTtree *Comstate(_IO_FILE *fp,bool canbreak);
ASTtree *LocalVarSeq(_IO_FILE *fp);
ASTtree *LocalVars(_IO_FILE *fp);
ASTtree *StateSeq(_IO_FILE * fp,bool canbreak);
ASTtree *State(_IO_FILE *fp,bool iselse);
ASTtree *Exp(_IO_FILE *fp,token_kind endsym);
void PreTraver(_IO_FILE *outputfile, ASTtree *t);
void Formatter(_IO_FILE *outputfile, ASTtree *t);
void InorderTraver(_IO_FILE *fp, ASTtree *t);