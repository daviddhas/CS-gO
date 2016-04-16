#pragma once

#include "Expression.hpp"

namespace csgo
{
    /* An object representing an assignment
    */
    class Assignment : public Expression
    {
    public:
        Assignment(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
            : lhs(lhs)
            , rhs(rhs)
        { }

        std::string toCode() const override
        {
            return lhs->toCode() + " = " + rhs->toCode();
        }

    private:
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;
        std::unique_ptr<Expression> rhs_managed;
    };
}