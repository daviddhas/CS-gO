#pragma once

#include <memory>
#include <vector>

#include "Expression.hpp"
#include "Assignment.hpp"

namespace csgo
{
    /* Returns an asignment when assigned to
    */
    class LValue : public Expression
    {
    public:
        static std::shared_ptr<Assignment> assign(std::shared_ptr<LValue> lhs, std::shared_ptr<Expression> rhs)
        {
            return std::make_shared<Assignment>(lhs, rhs);
        }
    };
}