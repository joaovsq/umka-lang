#include <math.h>

#include "umka_const.h"


void constInit(Consts *consts, ErrorFunc error)
{
    consts->error = error;
}


void constFree(Consts *consts)
{
}


void constUnary(Consts *consts, Const *arg, TokenKind tokKind, TypeKind typeKind)
{
    if (typeKind == TYPE_REAL || typeKind == TYPE_REAL32)
        switch (tokKind)
        {
            case TOK_MINUS: arg->realVal = -arg->realVal; break;
            default:        consts->error("Illegal operator");
        }
    else
        switch (tokKind)
        {
            case TOK_MINUS: arg->intVal = -arg->intVal; break;
            case TOK_NOT:   arg->intVal = !arg->intVal; break;
            case TOK_XOR:   arg->intVal = ~arg->intVal; break;
            default:        consts->error("Illegal operator");
        }
}


void constBinary(Consts *consts, Const *lhs, const Const *rhs, TokenKind tokKind, TypeKind typeKind)
{
    if (typeKind == TYPE_REAL || typeKind == TYPE_REAL32)
        switch (tokKind)
        {
            case TOK_PLUS:  lhs->realVal += rhs->realVal; break;
            case TOK_MINUS: lhs->realVal -= rhs->realVal; break;
            case TOK_MUL:   lhs->realVal *= rhs->realVal; break;
            case TOK_DIV:
            {
                if (rhs->realVal == 0)
                    consts->error("Division by zero");
                lhs->realVal /= rhs->realVal;
                break;
            }

            case TOK_EQEQ:      lhs->intVal = lhs->realVal == rhs->realVal; break;
            case TOK_NOTEQ:     lhs->intVal = lhs->realVal != rhs->realVal; break;
            case TOK_GREATER:   lhs->intVal = lhs->realVal >  rhs->realVal; break;
            case TOK_LESS:      lhs->intVal = lhs->realVal <  rhs->realVal; break;
            case TOK_GREATEREQ: lhs->intVal = lhs->realVal >= rhs->realVal; break;
            case TOK_LESSEQ:    lhs->intVal = lhs->realVal <= rhs->realVal; break;

            default:            consts->error("Illegal operator");
        }
    else
        switch (tokKind)
        {
            case TOK_PLUS:  lhs->intVal += rhs->intVal; break;
            case TOK_MINUS: lhs->intVal -= rhs->intVal; break;
            case TOK_MUL:   lhs->intVal *= rhs->intVal; break;
            case TOK_DIV:
            {
                if (rhs->intVal == 0)
                    consts->error("Division by zero");
                lhs->intVal /= rhs->intVal;
                break;
            }
            case TOK_MOD:
            {
                if (rhs->intVal == 0)
                    consts->error("Division by zero");
                lhs->intVal %= rhs->intVal;
                break;
            }

            case TOK_AND:   lhs->intVal &= rhs->intVal; break;
            case TOK_OR:    lhs->intVal |= rhs->intVal; break;
            case TOK_XOR:   lhs->intVal ^= rhs->intVal; break;

            case TOK_EQEQ:      lhs->intVal = lhs->intVal == rhs->intVal; break;
            case TOK_NOTEQ:     lhs->intVal = lhs->intVal != rhs->intVal; break;
            case TOK_GREATER:   lhs->intVal = lhs->intVal >  rhs->intVal; break;
            case TOK_LESS:      lhs->intVal = lhs->intVal <  rhs->intVal; break;
            case TOK_GREATEREQ: lhs->intVal = lhs->intVal >= rhs->intVal; break;
            case TOK_LESSEQ:    lhs->intVal = lhs->intVal <= rhs->intVal; break;

            default:            consts->error("Illegal operator");
        }
}


void constCallBuiltin(Consts *consts, Const *arg, BuiltinFunc builtinVal)
{
    switch (builtinVal)
    {
        case BUILTIN_REAL:
        case BUILTIN_REAL_LHS:  arg->realVal = arg->intVal; break;
        case BUILTIN_ROUND:     arg->intVal  = (int64_t)round(arg->realVal); break;
        case BUILTIN_TRUNC:     arg->intVal  = (int64_t)trunc(arg->realVal); break;
        case BUILTIN_FABS:      arg->realVal = fabs(arg->realVal); break;
        case BUILTIN_SQRT:
        {
            if (arg->realVal < 0)
                consts->error("sqrt() domain error");
            arg->realVal = sqrt(arg->realVal);
            break;
        }
        case BUILTIN_SIN:       arg->realVal = sin (arg->realVal); break;
        case BUILTIN_COS:       arg->realVal = cos (arg->realVal); break;
        case BUILTIN_ATAN:      arg->realVal = atan(arg->realVal); break;
        case BUILTIN_EXP:       arg->realVal = exp (arg->realVal); break;
        case BUILTIN_LOG:
        {
            if (arg->realVal <= 0)
                consts->error("log() domain error");
            arg->realVal = sqrt(arg->realVal);
            break;
        }
        default: consts->error("Illegal function");
    }
}

