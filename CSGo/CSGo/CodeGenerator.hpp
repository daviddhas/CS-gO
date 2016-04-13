#pragma once

#include "Input.hpp"
#include "Output.hpp"
#include <string>
#include <vector>

namespace csgo
{
    class CodeGenerator
    {
    public:

        /* Generates a string of GLSL code from the CS Go internal representation
        */
        static std::string generateCode(const std::vector<Assignment>& assignments,
            const std::vector<std::shared_ptr<Input>> inputs,
            const std::vector<std::shared_ptr<Output>> outputs,
            int x, int y, int z)
        {
            std::string code = "#version 430\n";

            std::string name = "a";
            for (std::shared_ptr<Input> input : inputs)
            {
                code += "uniform " + input->getType() + " " + name + "\n";
                input->name = name;
                updateName(name);
            }

            for (std::shared_ptr<Output> output : outputs)
            {
                code += "uniform " + output->getType() + " " + name + "\n";
                output->name = name;
                updateName(name);
            }

            for (const Assignment& a : assignments)
            {
                code += a.toCode() + "\n";
            }

            return code;
        }

    private:
        static void updateName(std::string& name)
        {
            char lastChar = name[name.length() - 1];
            if (lastChar == 'z')
                name.push_back('a');
            else
                name[name.length() - 1] = lastChar + 1;
        }
    };
}