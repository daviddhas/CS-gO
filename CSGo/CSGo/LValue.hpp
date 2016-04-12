#pragma once

#include <memory>

#include "Expression.hpp"
#include "Assignment.hpp"

namespace csgo
{
    class LValue : public Expression
    {
    public:
        Assignment operator=(const Expression& rhs)
        {
            return Assignment(*this, rhs);
        }
    };
}