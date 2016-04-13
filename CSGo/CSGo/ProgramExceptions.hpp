#pragma once

#include <stdexcept>

namespace csgo
{
    class UnfinishedProgramException : public std::runtime_error
    {
    public:
        UnfinishedProgramException()
            : runtime_error("Must call finish before running")
        { }

        virtual const char* what() const throw()
        {
            return runtime_error::what();
        }
    };

    class FinishedProgramException : public std::runtime_error
    {
    public:
        FinishedProgramException()
            : runtime_error("Cannot add to finished prorgam")
        { }

        virtual const char* what() const throw()
        {
            return runtime_error::what();
        }
    };
}