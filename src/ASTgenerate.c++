#include "ASTgenerate.h"
/*
ASTtree的具体使用函数
*/
using namespace std;
/**
 * @brief: ASTtree的free函数
 * @param {ASTtree} *k
 * @return {}
 */
void free0(ASTtree *k)
{
    if (k == NULL)
        return;
    free0(k->fchild);
    free0(k->schild);
    free(k);
}

/**
 * @brief: ASTtree的初始化赋值函数
 * @param {ASTtree} *k
 * @param {int} tt tokentype
 * @param {int} at ASTtype
 * @param {string} ttt tokentext
 * @return {*}
 */
ASTtree *ASTtreeinit(ASTtree *k, int tt, int at, string ttt)
{
    k = (ASTtree *)malloc(sizeof(ASTtree));
    k->tokentype = tt;
    char *m = (char *)ttt.c_str();
    k->tokentext = (char *)malloc(sizeof(char) * ttt.length());
    strcpy(k->tokentext, m);
    k->tokentype = tt;
    k->ASTtype = at;
    return k;
}
/**
 * @brief: 注释序列
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *NoteSeq(_IO_FILE *fp)
{
    ASTtree *b = NULL;
    if (token_type == NOTEK)
    {
        b = ASTtreeinit(b, NU, NOTEP, token_text[p - 1]);
        token_type = get_token(fp);
        return b;
    }
    b = ASTtreeinit(b, NU, NOTESEQ, "");
    b->fchild = ASTtreeinit(b->fchild, NU, NOTE, token_text[p - 1]);
    b->schild = ASTtreeinit(b->schild, NU, NOTESEQ, token_text[p - 1]);
    token_type = get_token(fp);
    if (token_type == NOTES)
        b->schild = NoteSeq(fp);
    return b;
}
/**
 * @brief: 项目生成
 * @param {_IO_FILE} *fp
 * @param {string} programname
 * @return {*}
 */
ASTtree *program(_IO_FILE *fp, string programname)
{
    token_type = get_token(fp);
    ASTtree *i = NULL;
    ASTtree *j = NULL;
    ASTtree *k = NULL;
    while (token_type == NOTES || token_type == NOTEK)
        k = NoteSeq(fp);
    while (token_type == MARCO)
        j = MarcoSeq(fp);
    if ((i = OutDefSeq(fp)) != NULL)
    {
        ASTtree *root;
        root = ASTtreeinit(root, NU, PROGRAM, programname);
        root->fchild = i;
        root->schild = k;
        root->tchild = j;
        return root;
    }
    else
    {
        cout << "error:there is no outsidedefine" << endl;
        return NULL;
    }
}

/**
 * @brief: 外部定义序列
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *OutDefSeq(_IO_FILE *fp)
{
    if (token_type == EOF)
        return NULL;
    ASTtree *t;
    t = ASTtreeinit(t, NU, OUTDEFSEQ, "");
    if (token_type == NOTES || token_type == NOTEK)
        t->tchild = NoteSeq(fp);
    if ((t->fchild = OutDef(fp)) == NULL)
        return NULL;
    t->schild = OutDefSeq(fp);
    token_type = get_token(fp);
    return t;
}
/**
 * @brief: 宏序列
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *MarcoSeq(_IO_FILE *fp)
{
    if (token_type == EOF)
        return NULL;
    ASTtree *t;
    t = ASTtreeinit(t, NU, MARCOSEQ, "");
    if ((t->fchild = Marco(fp)) == NULL)
        return NULL;
    t->schild = MarcoSeq(fp);
    if (token_type == NOTES || token_type == NOTEK)
        t->tchild = NoteSeq(fp);
    return t;
}
/**
 * @brief: 宏
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *Marco(_IO_FILE *fp)
{
    if (token_type != MARCO)
    {
        return NULL;
    }
    ASTtree *t;
    t = ASTtreeinit(t, NU, MARC, token_text[p - 1]);
    token_type = get_token(fp);
    return t;
}
/**
 * @brief: 外部定义
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *OutDef(_IO_FILE *fp)
{
    ASTtree *t;
    if (token_type == NOTES || token_type == NOTEK)
    {
        t = NoteSeq(fp);
        return t;
    }
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
/**
 * @brief: 函数定义
 * @param {_IO_FILE} *fp
 * @param {token_kind} type
 * @return {*}
 */
ASTtree *FunDef(_IO_FILE *fp, token_kind type)
{
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, FUNDEF, token_text[p - 1]);
    bool isre = false;
    for (int i = 0; i < func_num; i++)
        if (func[i].name == token_text[p - 1].c_str())
            isre = true;
    if (!isre)
    {
        func[func_num].name = (char *)malloc(sizeof(char) * token_text[p - 1].length());
        strcpy(func[func_num].name, token_text[p - 1].c_str());
    }
    t->fchild = ASTtreeinit(t->fchild, type, TYPEEXP, "");
    token_type = get_token(fp);
    if (token_type != RSP)
    {
        ASTtree *h = (ASTtree *)malloc(sizeof(ASTtree));
        h = ASTtreeinit(t, NU, FORPARSEQR, "");
        t->schild = h;
        h->fchild = ForParSeq(fp, isre);
        func_num++;
    }
    token_type = get_token(fp);
    if (token_type == SEMI)
    {
        token_type = get_token(fp);
        if (token_type == NOTES || token_type == NOTEK)
            t->tchild = NoteSeq(fp);
        return t;
    }
    else if (token_type == LLP)
    {
        token_type = get_token(fp); //左大括号后面的第一个token
        t->tchild = Comstate(fp, false);
        return t;
    }
    cout << "error:function body or declare is incomplete" << endl;
    exit(1);
}
/**
 * @brief: 函数使用
 * @param {_IO_FILE} *fp
 * @param {int} funnum
 * @return {*}
 */
ASTtree *FunUse(_IO_FILE *fp, int funnum)
{
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, FUNUSE, token_text[p - 1]);
    token_type = get_token(fp);
    if (token_type != LSP)
    {
        cout << "error:missing par" << endl;
        exit(1);
    }
    ASTtree *h = (ASTtree *)malloc(sizeof(ASTtree));
    t->fchild = h;
    token_type = get_token(fp);
    int parnum = 0;
    while (1)
    {
        if (token_type != IDENT && token_type != INT_CONST && token_type != FLOAT_CONST && token_type != CHAR_CONST)
        {
            cout << "error:par is incomplete" << endl;
            exit(1);
        }
        h->fchild = (ASTtree *)malloc(sizeof(ASTtree));
        h->fchild = ASTtreeinit(h, token_type, PAR, token_text[p - 1]);
        h = h->fchild;
        parnum++;
        token_type = get_token(fp);
        if (parnum == func[funnum].par)
        {
            if (token_type != RSP)
            {
                cout << "error:par is too much" << endl;
                exit(1);
            }
            token_type = get_token(fp); //这里是RSP后一个符号
            return t;
        }
        if (token_type != COMMA)
        {
            cout << "error:par is wrong" << endl;
            exit(1);
        }
        token_type = get_token(fp);
    }
    cout << "error :missing token;" << endl;
    exit(1);
}
/**
 * @brief: 语句块
 * @param {_IO_FILE} *fp
 * @param {bool} canbreak
 * @return {*}
 */
ASTtree *Comstate(_IO_FILE *fp, bool canbreak)
{
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, COMSTATE, "");
    if (token_type == NOTES || token_type == NOTEK)
        t->tchild = NoteSeq(fp);
    if (token_type == RLP)
    {
        token_type = get_token(fp);
        if (token_type == NOTES || token_type == NOTEK)
            t->tchild = NoteSeq(fp);
        return t;
    }
    else if (token_type == LLP)
    {
        token_type = get_token(fp);
        if (token_type == NOTES || token_type == NOTEK)
            t->tchild = NoteSeq(fp);
        t->schild = Comstate(fp, canbreak);
    }
    else if (token_type == EOF)
    {
        cout << "error:comstate is incomplete" << endl;
        exit(1);
    }
    else
    {
        if (token_type == INT || token_type == FLOAT || token_type == CHAR)
            t->fchild = LocalVarSeq(fp);
        else
            t->fchild = NULL;
        t->schild = StateSeq(fp, canbreak);
    }
    if (token_type != RLP)
    {
        cout << "error:comstate is incomplete" << endl;
        exit(1);
    }
    token_type = get_token(fp);
    return t;
}
/**
 * @brief: 语句序列
 * @param {_IO_FILE} *fp
 * @param {bool} canbreak
 * @return {*}
 */
ASTtree *StateSeq(_IO_FILE *fp, bool canbreak)
{
    ASTtree *t;
    if (token_type == RLP)
    {
        return NULL;
    }
    t = ASTtreeinit(t, NU, STATESEQ, "");
    t->fchild = State(fp, false);
    if (token_type == NOTES || token_type == NOTEK)
        t->tchild = NoteSeq(fp);
    if (t->fchild == NULL)
    {
        cout << "error:the state is incomplete" << endl;
        exit(1);
    }
    t->schild = StateSeq(fp, canbreak);
    return t;
}
/**
 * @brief: 语句
 * @param {_IO_FILE} *fp
 * @param {bool} iselse
 * @param {bool} canbreak
 * @return {*}
 */
ASTtree *State(_IO_FILE *fp, bool iselse)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, STATES, "");
    ASTtree *h = ASTtreeinit(h, NU, FORGR, "");
    bool b;
    switch (token_type)
    {
    case BREAK:
        if (!canbreak)
        {
            cout << "error:this state can't break" << endl;
            exit(1);
        }
        token_type = get_token(fp);
        token_type = get_token(fp);
        t->tokentype = BREAK;
        break;
    case CONTINUE:
        if (!canbreak)
        {
            cout << "error:this state can't continue" << endl;
            exit(1);
        }
        token_type = get_token(fp);
        token_type = get_token(fp);
        t->tokentype = CONTINUE;
        break;
    case IF:
        token_type = get_token(fp);
        if (token_type != LSP)
        {
            cout << "error:if is incomplete" << endl;
            exit(1);
        }
        token_type = get_token(fp);
        t->fchild = Exp(fp, RSP);
        t->schild = State(fp, false);
        if (token_type == ELSE)
        {
            t->tchild = State(fp, true);
        }
        t->tokentype = IF;
        break;
    case ELSE:
        if (!iselse)
        {
            cout << "error:else is incomplete" << endl;
            exit(1);
        }
        token_type = get_token(fp);
        if (token_type == IF)
        {
            t->tokentype = ELSEIF;
            token_type = get_token(fp);
        }
        else
            t->tokentype = ELSE;
        if (token_type != LSP && t->tokentype == ELSEIF)
        {
            cout << "error:else is incomplete" << endl;
            exit(1);
        }
        if (t->tokentype == ELSEIF)
        {
            token_type = get_token(fp);
            t->fchild = Exp(fp, RSP);
            t->schild = State(fp, false);
            t->tchild = State(fp, true);
            t->tchild->tokentype = ELSE;
        }
        else
        {
            t->tchild = State(fp, false);
        }
        break;
    case WHILE:
        token_type = get_token(fp);
        if (token_type != LSP)
        {
            cout << "error:while is incomplete" << endl;
            exit(1);
        }
        token_type = get_token(fp);
        t->fchild = Exp(fp, RSP);
        b = canbreak;
        canbreak = true;
        t->schild = State(fp, false);
        canbreak = b;
        t->tokentype = WHILE;
        break;
    case FOR:
        token_type = get_token(fp);
        if (token_type != LSP)
        {
            cout << "error:for is incomplete" << endl;
            exit(1);
        }
        token_type = get_token(fp);
        h->fchild = Exp(fp, FORPR);
        h->schild = Exp(fp, FORPR);
        h->tchild = Exp(fp, RSP);
        t->fchild = h;
        b = canbreak;
        canbreak = true;
        t->schild = State(fp, false);
        t->tokentype = FOR;
        canbreak = b;
        break;
    case LSP:
        t = Exp(fp, RSP);
        break;
    case IDENT:
    case INT_CONST:
    case FLOAT_CONST:
    case CHAR_CONST:
        t->fchild = Exp(fp, SEMI);
        break;
    case LLP:
        token_type = get_token(fp);
        t = Comstate(fp, canbreak);
        break;
    case RLP:
        token_type = get_token(fp);
        return NULL;
    case RETURN:
        token_type = get_token(fp);
        t->fchild = Exp(fp, SEMI);
        t->tokentype = RETURN;
        break;
    default:
        while (token_type != SEMI)
        {
            token_type = get_token(fp);
        }
        token_type = get_token(fp);
        t = ASTtreeinit(t, NU, EXP, "");
        break;
    }
    return t;
}
/**
 * @brief: 表达式
 * @param {_IO_FILE} *fp
 * @param {token_kind} endsym
 * @return {*}
 */
ASTtree *Exp(_IO_FILE *fp, token_kind endsym)
{
    ASTtree *t;
    t = (ASTtree *)malloc(sizeof(ASTtree));
    if (token_type == endsym)
        return NULL;
    if (endsym == SEMI)
        t = ASTtreeinit(t, NU, EXP, "");
    else if (endsym == RSP)
        t = ASTtreeinit(t, BG, EXP, "");
    else
    {
        t = ASTtreeinit(t, FORPR, EXP, "");
        endsym = SEMI;
    }
    if (token_type == IDENT)
        for (int i = 0; i < func_num; i++)
            if (func[i].name == token_text[p - 1])
            {
                t->fchild = FunUse(fp, i);
                token_type = get_token(fp);
                return t;
            }
    stack<token_kind> op;
    stack<ASTtree *> opn;
    op.push(BG);
    token_kind type = token_type;
    while (token_type != BG || op.top() != BG)
    {
        if (token_type == IDENT || token_type == INT_CONST || token_type == CHAR_CONST || token_type == FLOAT_CONST)
        {
            ASTtree *h = (ASTtree *)malloc(sizeof(ASTtree));
            h = ASTtreeinit(h, IDENT, VAR, token_text[p - 1]);
            opn.push(h);
            token_type = get_token(fp);
        }
        else if (token_type == BG || token_type == LSP || token_type == RSP || token_type == ADD || token_type == MINUS || token_type == MULTI || token_type == DIVIDE || token_type == REMAIN || token_type == EQ || token_type == NEQ || token_type == LEQ || token_type == MEQ || token_type == LESS || token_type == MORE || token_type == ASSIGN || token_type == SEMI)
        {
            switch (precede(token_type, op.top()))
            {
            case 1:
                if (opn.size() < 2)
                {
                    cout << "error:exp is incomplete" << endl;
                    exit(1);
                }
                ASTtree *h1, *h2, *hr;
                h2 = opn.top();
                opn.pop();
                h1 = opn.top();
                opn.pop();
                type = op.top();
                op.pop();
                hr = ASTtreeinit(hr, type, BINARY, "");
                hr->fchild = h1;
                hr->schild = h2;
                opn.push(hr);
                break;
            case 0:
                op.push(token_type);
                token_type = get_token(fp);
                break;
            case (-1):
                if (op.size() < 1)
                {
                    cout << "error:exp is incomplete" << endl;
                    exit(1);
                }
                type = op.top();
                op.pop();
                token_type = get_token(fp);
                break;
            default:
                if (token_type == endsym)
                    token_type = BG;
                break;
            }
        }
        else if (token_type == endsym)
            token_type = BG;
        else
        {
            cout << "error:exp is incomplete" << endl;
            exit(1);
        }
    }
    if (opn.size() == 1 && op.top() == BG)
    {
        t->fchild = opn.top();
        opn.pop();
        token_type = get_token(fp);
        return t;
    }
    else
    {
        cout << "error:exp is incomplete" << endl;
        exit(1);
    }
}
/**
 * @brief:本地变量序列
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *LocalVarSeq(_IO_FILE *fp)
{
    if (token_type == EOF)
    {
        cout << "error:localvarseq is incomplete" << endl;
        return NULL;
    }
    if (token_type == SEMI)
        token_type = get_token(fp);
    if (token_type != INT && token_type != FLOAT && token_type != CHAR)
    {
        return NULL;
    }
    ASTtree *t;
    t = ASTtreeinit(t, NU, LOCALVARSEQ, "");
    t->fchild = LocalVars(fp);
    if (token_type == NOTES || token_type == NOTEK)
        t->tchild = NoteSeq(fp);
    t->schild = LocalVarSeq(fp);
    return t;
}
/**
 * @brief: 本地变量
 * @param {_IO_FILE} *fp
 * @return {*}
 */
ASTtree *LocalVars(_IO_FILE *fp)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, LOCALVARS, "");
    t->fchild = ASTtreeinit(t->fchild, token_type, TYPEEXP, "");
    token_kind y = token_type;
    token_type = get_token(fp); //变量名
    token_type = get_token(fp); //变量名后符号
    t->schild = VarSeq(fp, y);
    return t;
}
/**
 * @brief: 函数参数序列
 * @param {_IO_FILE} *fp
 * @param {bool} isre
 * @return {*}
 */
ASTtree *ForParSeq(_IO_FILE *fp, bool isre)
{
    if (token_type == COMMA)
        token_type = get_token(fp);
    if (token_type == RSP)
        return NULL;
    ASTtree *t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, FORPARSEQ, "");
    t->fchild = ForPars(fp);
    func[func_num].par++;
    t->schild = ForParSeq(fp, isre);
    return t;
}
/**
 * @brief: 函数参数
 * @param {_IO_FILE} *fp
 * @return {*}
 */
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
/**
 * @brief: 变量序列
 * @param {_IO_FILE} *fp
 * @param {token_kind} type
 * @return {*}
 */
ASTtree *VarSeq(_IO_FILE *fp, token_kind type)
{
    ASTtree *h;
    h = ASTtreeinit(h, NU, VARSEQ, "");
    ASTtree *r = h;
    h->fchild = ASTtreeinit(h->fchild, IDENT, VAR, token_text[p - 1]);
    while (1)
    {
        if (token_type == ASSIGN)
        {
            token_type = get_token(fp);
            if (JudgeIdentConst(type, token_type))
            {
                token_type = get_token(fp);
            }
            else
            {
                cout << "error:the assighment is illegal" << endl;
                exit(1);
            }
        }
        switch (token_type)
        {
        case SEMI:
            token_type = get_token(fp);
            return r;
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
            q = ASTtreeinit(q, NU, VARSEQ, "");
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
/**
 * @brief: 外部变量定义
 * @param {_IO_FILE} *fp
 * @param {token_kind} type
 * @return {*}
 */
ASTtree *OutVarDef(_IO_FILE *fp, token_kind type)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, OUTVARDEF, "");
    t->fchild = ASTtreeinit(t->fchild, type, TYPEEXP, "");
    t->schild = VarSeq(fp, type);
    return t;
}
/**
 * @brief: ASTtree显示
 * @param {_IO_FILE} *outputfile
 * @param {ASTtree} *t
 * @return {*}
 */
void PreTraver(_IO_FILE *outputfile, ASTtree *t)
{
    if (t == NULL)
        return;
    string s = "";
    switch (t->ASTtype)
    {
    case PROGRAM:
        fprintf(outputfile, "program %s:\n", t->tokentext);
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        printtab(++tab, outputfile);
        fprintf(outputfile, "external defined sequence:\n");
        PreTraver(outputfile, t->fchild);
        tab--;
        break;
    case NOTESEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    case NOTE:
        fprintf(outputfile, "note:%s:\n", t->tokentext);
        break;
    case MARCOSEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        break;
    case MARC:
        fprintf(outputfile, "macro:%s:\n", t->tokentext);
        break;
    case OUTDEFSEQ:
        PreTraver(outputfile, t->fchild);
        fprintf(outputfile, "\n");
        PreTraver(outputfile, t->schild);
        break;
    case OUTDEF:
        printf("generate wrong\n");
        break;
    case OUTVARDEF:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    case TYPEEXP:
        if (t->tokentype == INT)
            s += "integer";
        else if (t->tokentype == FLOAT)
            s += "float";
        else if (t->tokentype == CHAR)
            s += "char";
        else
            s += "error";
        istab=false;
        fprintf(outputfile, "type: %s ", s.c_str());
        break;
    case VARSEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        break;
    case VAR:
        fprintf(outputfile, "\n");
        istab=false;
        fprintf(outputfile, "ID: %s ", t->tokentext);
        PreTraver(outputfile, t->tchild);
        break;
    case FUNDEF:
        printtab(tab++, outputfile);
        fprintf(outputfile, "function  %s  's definition:\n", t->tokentext);
        printtab(tab++, outputfile);
        fprintf(outputfile, "return\n");
        PreTraver(outputfile, t->fchild);
        fprintf(outputfile, "\n");
        tab--;
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        tab--;
        break;
    case FORPARSEQR:
        printtab(tab++, outputfile);
        fprintf(outputfile, "formal parameters:\n");
        PreTraver(outputfile, t->fchild);
        tab--;
        break;
    case FORPARSEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    case FORPARS:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        fprintf(outputfile, "\n");
        break;
    case COMSTATE:
        printtab(tab++, outputfile);
        fprintf(outputfile, "{\n");
        tab++;
        if (t->fchild != NULL)
        {
            printtab(--tab, outputfile);
            fprintf(outputfile, "local variable definition:\n");
            tab++;
        }
        PreTraver(outputfile, t->fchild);
        tab--;
        PreTraver(outputfile, t->schild);
        printtab(--tab, outputfile);
        fprintf(outputfile, "}\n");
        break;
    case LOCALVARSEQ:
        PreTraver(outputfile, t->fchild);
        fprintf(outputfile, "\n");
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        break;
    case LOCALVARS:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        break;
    case STATESEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        PreTraver(outputfile, t->tchild);
        break;
    case STATES:
        if (t->tokentype == IF)
            s += "if";
        else if (t->tokentype == ELSE)
            s += "else";
        else if (t->tokentype == ELSEIF)
            s += "else if";
        else if (t->tokentype == WHILE)
            s += "while";
        else if (t->tokentype == RETURN)
            s += "return";
        else if (t->tokentype == NU)
            ;
        else
            s += "error";
        printtab(tab++, outputfile);
        fprintf(outputfile, "%s \n", s.c_str());
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        tab--;
        PreTraver(outputfile, t->tchild);
        break;
    case EXP:
        istab=false;
        fprintf(outputfile, "expression:");
        PreTraver(outputfile, t->fchild); //此处应该是一个中序遍历
        PreTraver(outputfile, t->tchild);
        fprintf(outputfile, "\n");
        break;
    case BINARY:
        if (t->tokentype == ADD)
            s += "+";
        else if (t->tokentype == ASSIGN)
            s += "=";
        else if (t->tokentype == MINUS)
            s += "-";
        else if (t->tokentype == MULTI)
            s += "*";
        else if (t->tokentype == DIVIDE)
            s += "/";
        else if (t->tokentype == REMAIN)
            s += "%";
        else if (t->tokentype == EQ)
            s += "==";
        else if (t->tokentype == NEQ)
            s += "!=";
        else if (t->tokentype == LESS)
            s += "<";
        else if (t->tokentype == LEQ)
            s += "<=";
        else if (t->tokentype == MORE)
            s += ">";
        else if (t->tokentype == MEQ)
            s += ">=";
        else
            s += "error";
        fprintf(outputfile, "\n");
        istab=false;
        fprintf(outputfile, "calculate mode: %s ", s.c_str());
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    default:
        break;
    }
}
/**
 * @brief: 格式化函数
 * @param {_IO_FILE} *outputfile
 * @param {ASTtree} *t
 * @return {*}
 */
void Formatter(_IO_FILE *outputfile, ASTtree *t)
{
    if (t == NULL)
        return;
    string s = "";
    int l = 1;
    if(!istab){
        printtab(tab,outputfile);
        istab=true;
    }
    switch (t->ASTtype)
    {
    case PROGRAM:
        Formatter(outputfile, t->schild);
        Formatter(outputfile, t->tchild);
        Formatter(outputfile, t->fchild);
        break;
    case NOTESEQ:
        // Formatter(outputfile, t->fchild);
        // Formatter(outputfile, t->schild);
        break;
    case NOTE:
        // fprintf(outputfile, "//%s\n", t->tokentext);
        // printtab(tab,outputfile);
        break;
    case MARC:
        fprintf(outputfile, "#");
        fprintf(outputfile, t->tokentext);
        fprintf(outputfile, "\n");
        istab=false;
        break;
    case OUTDEF:
        printf("generate wrong\n");
        break;
    case FUNUSE:
        s += t->tokentext;
        fprintf(outputfile, "%s(", s.c_str());
        Formatter(outputfile, t->fchild);
        break;
    case PAR:
        s += t->tokentext;
        if (t->fchild)
            s += ",";
        else
            s += ")";
        fprintf(outputfile, "%s", s.c_str());
        Formatter(outputfile, t->fchild);
        break;
    case TYPEEXP:
        if (t->tokentype == INT)
            s += "int";
        else if (t->tokentype == FLOAT)
            s += "float";
        else if (t->tokentype == CHAR)
            s += "char";
        else if (t->tokentype == VOID)
            s += "void";
        else
            s += "error";
        fprintf(outputfile, "%s", s.c_str());
        break;
    case VARSEQ:
        // istab=false;
        Formatter(outputfile, t->fchild);
        if (t->schild)
            fprintf(outputfile, ",");
        else
        {
            fprintf(outputfile, ";");
            Formatter(outputfile, t->tchild);
            fprintf(outputfile, "\n");
            istab=false;
        }
        Formatter(outputfile, t->schild);
        break;
    case VAR:
        fprintf(outputfile, " %s", t->tokentext);
        Formatter(outputfile, t->fchild);
        Formatter(outputfile, t->schild);
        Formatter(outputfile, t->tchild);
        break;
    case NOTEP:
        // s+=t->tokentext;
        // fprintf(outputfile,"/*%s*/\n",s.c_str());
        // printtab(tab,outputfile);
        break;
    case FUNDEF:
        Formatter(outputfile, t->fchild);
        fprintf(outputfile, " %s(", t->tokentext);
        Formatter(outputfile, t->schild);
        fprintf(outputfile, ")");
        if (t->tchild)
            Formatter(outputfile, t->tchild);
        else
        {
            fprintf(outputfile, ";\n");
            istab=false;
        }
        break;
    case FORPARSEQR:
        Formatter(outputfile, t->fchild);
        break;
    case FORPARSEQ:
        Formatter(outputfile, t->fchild);
        if (t->schild)
            fprintf(outputfile, ",");
        Formatter(outputfile, t->schild);
        break;
    case FORPARS:
        Formatter(outputfile, t->fchild);
        Formatter(outputfile, t->schild);
        break;
    case COMSTATE:
        fprintf(outputfile, "{\n");
        tab++;
        istab=false;
        Formatter(outputfile, t->tchild);
        Formatter(outputfile, t->fchild);
        Formatter(outputfile, t->schild);
        printtab(tab-1,outputfile);
        fprintf(outputfile, "}\n");
        tab--;
        istab=false;
        break;
    case FORGR:
        Formatter(outputfile, t->fchild);
        fprintf(outputfile, ";");
        Formatter(outputfile, t->schild);
        fprintf(outputfile, ";");
        Formatter(outputfile, t->tchild);
        break;
    case MARCOSEQ:
    case OUTDEFSEQ:
    case OUTVARDEF:
    case LOCALVARSEQ:
    case LOCALVARS:
    case STATESEQ:
        Formatter(outputfile, t->fchild);
        Formatter(outputfile, t->schild);
        Formatter(outputfile, t->tchild);
        break;
    case STATES:
        switch (t->tokentype)
        {
        case IF:
            s += "if( ";
            break;
        case ELSE:
            s += "else ";
            break;
        case ELSEIF:
            s += "else if( ";
            break;
        case WHILE:
            s += "while( ";
            break;
        case RETURN:
            s += "return ";
            break;
        case CONTINUE:
            s += "continue;";
            break;
        case BREAK:
            s += "break;";
            break;
        case FOR:
            s += "for( ";
            break;
        case NU:
            break;
        default:
            s += "error";
        }
        fprintf(outputfile, "%s", s.c_str());
        Formatter(outputfile, t->fchild);
        if (t->tokentype == IF || t->tokentype == ELSEIF || t->tokentype == WHILE || t->tokentype == FOR)
            fprintf(outputfile, ")");
        if (t->tokentype == IF || t->tokentype == ELSE || t->tokentype == ELSEIF || t->tokentype == WHILE || t->tokentype == FOR)
        {
            fprintf(outputfile, "\n");
            if (t->schild)
                if (t->schild->ASTtype != COMSTATE)
                {
                    tab++;
                    l = 0;
                }
            istab=false;
        }
        if(t->tokentype==BREAK||t->tokentype==CONTINUE){
            fprintf(outputfile,"\n");
            istab=false;
        }
        Formatter(outputfile, t->schild);
        if (l == 0)
            tab--;
        Formatter(outputfile, t->tchild);
        break;
    case EXP:
        if (t->fchild)
            if (t->fchild->ASTtype == FUNUSE)
                Formatter(outputfile, t->fchild);
        InorderTraver(outputfile, t->fchild);
        if (t->tokentype == NU){
            fprintf(outputfile, ";");
            fprintf(outputfile,"\n");
            istab=false;
            }
        break;
    default:
        break;
    }
}
/**
 * @brief: 中序遍历识别并输出表达式
 * @param {_IO_FILE} *fp
 * @param {ASTtree} *t
 * @return {*}
 */
void InorderTraver(_IO_FILE *fp, ASTtree *t)
{
    if (t == NULL)
        return;
    InorderTraver(fp, t->fchild);
    switch (t->ASTtype)
    {
    case VAR:
        fprintf(fp, "%s ", t->tokentext);
        break;
    case BINARY:
        switch (t->tokentype)
        {
        case ADD:
            fprintf(fp, "+ ");
            break;
        case ASSIGN:
            fprintf(fp, "= ");
            break;
        case MINUS:
            fprintf(fp, "- ");
            break;
        case MULTI:
            fprintf(fp, "* ");
            break;
        case DIVIDE:
            fprintf(fp, "/ ");
            break;
        case REMAIN:
            fprintf(fp, "% ");
            break;
        case EQ:
            fprintf(fp, "== ");
            break;
        case NEQ:
            fprintf(fp, "!= ");
            break;
        case LESS:
            fprintf(fp, "< ");
            break;
        case LEQ:
            fprintf(fp, "<= ");
            break;
        case MORE:
            fprintf(fp, "> ");
            break;
        case MEQ:
            fprintf(fp, ">= ");
            break;
        case LSP:
            fprintf(fp, "( ");
            break;
        case RSP:
            fprintf(fp, ") ");
            break;
        default:
            break;
        }
        break;
    }
    InorderTraver(fp, t->schild);
}