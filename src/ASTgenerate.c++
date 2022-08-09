#include "ASTgenerate.h"
using namespace std;
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
    if ((t->fchild = OutDef(fp)) == NULL)
        return NULL;
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
        token_type = get_token(fp); //左大括号后面的第一个token
        t->tchild = Comstate(fp);
        token_type = get_token(fp); //右大括号后面的东西
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
        token_type = get_token(fp);
        t->schild = Comstate(fp);
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
        t->schild = StateSeq(fp);
    }
    if (token_type != RLP)
    {
        cout << "error:comstate is incomplete" << endl;
        exit(1);
    }
    token_type = get_token(fp);
    return t;
}

ASTtree *StateSeq(_IO_FILE *fp)
{
    ASTtree *t;
    if (token_type == RLP)
    {
        return NULL;
    }
    t = ASTtreeinit(t, NU, STATESEQ, "");
    t->fchild = State(fp, false);
    if (t->fchild == NULL)
    {
        cout << "error:the state is incomplete" << endl;
        exit(1);
    }
    t->schild = StateSeq(fp);
    return t;
}

ASTtree *State(_IO_FILE *fp, bool iselse)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, STATES, "");
    switch (token_type)
    {
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
        if (token_type != LSP&&t->tokentype==ELSEIF)
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
            t->tchild->tokentype=ELSE;
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
        t->schild = State(fp, false);
        t->tokentype = WHILE;
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
        t = Comstate(fp);
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
        break;
    }
    return t;
}

ASTtree *Exp(_IO_FILE *fp, token_kind endsym)
{
    ASTtree *t;
    stack<token_kind> op;
    stack<ASTtree *> opn;
    op.push(BG);
    if (token_type == endsym)
        return NULL;
    t = (ASTtree *)malloc(sizeof(ASTtree));
    t = ASTtreeinit(t, NU, EXP, "");
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
    t->schild = LocalVarSeq(fp);
    return t;
}

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

ASTtree *VarSeq(_IO_FILE *fp, token_kind type)
{
    ASTtree *h;
    h = ASTtreeinit(h, NU, VARSEQ, "");
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

ASTtree *OutVarDef(_IO_FILE *fp, token_kind type)
{
    ASTtree *t;
    t = ASTtreeinit(t, NU, OUTVARDEF, "");
    t->fchild = ASTtreeinit(t->fchild, type, TYPEEXP, "");
    t->schild = VarSeq(fp, type);
    return t;
}

void PreTraver(_IO_FILE *outputfile, ASTtree *t)
{
    if (t == NULL)
        return;
    string s = "";
    switch (t->ASTtype)
    {
    case PROGRAM:
        fprintf(outputfile, "program %s:\n", t->tokentext);
        printtab(++tab, outputfile);
        fprintf(outputfile, "external defined sequence:\n");
        PreTraver(outputfile, t->fchild);
        tab--;
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
        printtab(tab, outputfile);
        fprintf(outputfile, "type: %s ", s.c_str());
        break;
    case VARSEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    case VAR:
        fprintf(outputfile, "\n");
        printtab(tab, outputfile);
        fprintf(outputfile, "ID: %s ", t->tokentext);
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
        break;
    case LOCALVARS:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    case STATESEQ:
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    case STATES:
        if (t->tokentype == IF)
            s += "if";
        else if (t->tokentype == ELSE)
            s += "else";
        else if (t->tokentype == ELSEIF)
            s+="else if";
        else if (t->tokentype == WHILE)
            s += "while";
        else if (t->tokentype == RETURN)
            s += "return";
        else if (t->tokentype == NU);
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
        printtab(tab, outputfile);
        fprintf(outputfile, "expression:");
        PreTraver(outputfile, t->fchild); //此处应该是一个中序遍历
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
        printtab(tab, outputfile);
        fprintf(outputfile, "calculate mode: %s ", s.c_str());
        PreTraver(outputfile, t->fchild);
        PreTraver(outputfile, t->schild);
        break;
    default:
        break;
    }
}