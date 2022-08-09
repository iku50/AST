#pragma once
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
    EOF,         // eof
    NU,          // null
    ERROR_TOKEN, // wrong token
    IDENT,       // identifier
    INT_CONST,   // integer constant
    FLOAT_CONST, // float constant
    CHAR_CONST,  // char constant
    INT,         // int
    FLOAT,       // float
    CHAR,        // char
    VOID,        // void
    CONST,       // const
    IF,          // if
    ELSE,        // else
    ELSEIF,      // elseif
    RETURN,   // return
    WHILE,    // while
    FOR,      // for
    BREAK,    // break
    CONTINUE, // continue
    CASE,     // case
    ADD,      //+
    ADDS,     //++
    MINUS,    //-
    MINUSS,   //--
    MULTI,    //*
    DIVIDE,   ///
    REMAIN,   //%
    MORE,     //>
    LESS,     //<
    MEQ,      //>=
    LEQ,      //<=
    EQ,       //==
    NEQ,      //!=
    ASSIGN,   //=
    AND,      //&&
    OR,       //||
    LSP,      //(
    RSP,      //)
    LMP,      //[
    RMP,      //]
    LLP,      //{
    RLP,      //}
    SEMI,     //;
    COMMA,    //,
    COLON,    //:
    MARCO,    //#
    NOTES,    //注释
    BG,       //开始结束标记
};
unordered_map<string, token_kind> keyword={
    {"void", VOID},
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
    {"CONST", CONST},};
int precede(token_kind a, token_kind b);
extern string token_text[99];
extern int p ;
extern token_kind token_type ;
token_kind get_token(_IO_FILE *fp);
bool cifafenxi(_IO_FILE *outputfile, int i, string token);
bool JudgeIdentConst(token_kind Ident, token_kind Const);
void Start(int argc, char **argv);
void printtab(int n,_IO_FILE *outputfile);
void yufafenxi(_IO_FILE *fp, string filename,_IO_FILE *outputfile,int mode);