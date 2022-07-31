#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
enum token_kind
{
    ERROR_TOKEN,
    IDENT,
    INT_CONST,
    FLOAT_CONST,
    CHAR_CONST,
    INT_ARRAY,
    FLOAT_ARRAY,
    CHAR_ARRAY,
    INT,
    FLOAT,
    CHAR,
    CONST,
    IF,
    ELSE,
    RETURN,
    WHILE,
    FOR,
    BREAK,
    CONTINUE,
    CASE,
    ADD,
    MINUS,
    MULTI,
    DIVIDE,
    REMAIN,
    MORE,
    LESS,
    MEQ,
    LEQ,
    EQ,
    ASSIGN,
    AND,
    OR,
    LSP,
    RSP,
    LMP,
    RMP,
    LLP,
    RLP,
    SEMI,
    COMMA,
    COLON,
    MARCO,
    NOTES,
};

unordered_map<string, int> keyword = {
    {"if", IF}, {"else", ELSE}, {"while", WHILE}, {"return", RETURN}, {"for", FOR}, {"break", BREAK}, {"continue", CONTINUE}, {"case", CASE}, {"int", INT}, {"char", CHAR}, {"float", FLOAT}, {"CONST", CONST}};
string token_text[99];
string tokenText;
int line = -1;
int get_token(_IO_FILE *fp);
bool cifafenxi(int i,string token);
void Start(int argc,char **argv);