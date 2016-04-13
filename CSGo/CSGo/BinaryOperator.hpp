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
        BinaryOperator(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs, Op op)
            : lhs(lhs)
            , rhs(rhs)
            , op(op)
        { }

        std::string toCode() const override
        {
            std::string opString;
            switch (op)
            {
            case PLUS:
                opString = "+";
            case MINUS:
                opString = "-";
            case TIMES:
                opString = "*";
            default:
                opString = "/";
            }

            return "(" + lhs->toCode() + opString + rhs->toCode() + ")";
        }

    private:
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;
        Op op;
    };

    std::shared_ptr<BinaryOperator> operator+(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
    {
        return std::make_shared<BinaryOperator>(lhs, rhs, Op::PLUS);
    }
}