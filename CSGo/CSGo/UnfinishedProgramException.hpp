#pragma once

#include <stdexcept>

namespace csgo
{
    class UnfinishedProgramException : public std::runtime_error
    {
    public:
        UnfinishedProgramException(std::string err)
            : runtime_error(err)
        { }

        virtual const char* what() const throw()
        {
            return runtime_error::what();
        }
    };
}