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
        Assignment operator=(const Expression& rhs)
        {
            return Assignment(*this, rhs);
        }
    };
}