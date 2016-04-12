#pragma once

#include <memory>
#include "Expression.hpp"

namespace csgo
{
    class BinaryOperator : public Expression
    {
    public:
        BinaryOperator(const Expression& lhs, const Expression& rhs)
            : lhs(lhs)
            , rhs(rhs)
        { }

    private:
        Expression lhs;
        Expression rhs;
    };

    BinaryOperator operator+(const Expression& lhs, const Expression& rhs)
    {
        return BinaryOperator(lhs, rhs);
    }
}