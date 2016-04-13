#pragma once

#include "Expression.hpp"

namespace csgo
{
    /* An object representing an assignment
    */
    class Assignment : public Expression
    {
    public:
        Assignment(const Expression& lhs, const Expression& rhs)
            : lhs(lhs)
            , rhs(rhs)
        { }

    private:
        Expression lhs;
        Expression rhs;
    };
}