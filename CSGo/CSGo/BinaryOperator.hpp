#pragma once

#include <memory>
#include "Expression.hpp"

namespace csgo
{
    enum Op
    {
        PLUS, MINUS, TIMES, DIVIDE
    };

    class BinaryOperator : public Expression
    {
    public:
        BinaryOperator(const Expression& lhs, const Expression& rhs, Op op)
            : lhs(lhs)
            , rhs(rhs)
            , op(op)
        { }

    private:
        Expression lhs;
        Expression rhs;
        Op op;
    };

    BinaryOperator operator+(const Expression& lhs, const Expression& rhs)
    {
        return BinaryOperator(lhs, rhs, Op::PLUS);
    }

    BinaryOperator operator-(const Expression& lhs, const Expression& rhs)
    {
        return BinaryOperator(lhs, rhs, Op::MINUS);
    }

    BinaryOperator operator*(const Expression& lhs, const Expression& rhs)
    {
        return BinaryOperator(lhs, rhs, Op::TIMES);
    }

    BinaryOperator operator/(const Expression& lhs, const Expression& rhs)
    {
        return BinaryOperator(lhs, rhs, Op::DIVIDE);
    }
}