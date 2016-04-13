#pragma once

#include "Input.hpp"
#include "Output.hpp"
#include <string>
#include <vector>
#include <iostream>

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

            code += genUniforms(inputs, outputs);

            code += openMain(x, y, z);

            for (const Assignment& a : assignments)
            {
                code += a.toCode() + ";\n";
            }

            code += closeMain();

            std::cout << code;
            return code;
        }

    private:

        static std::string openMain(int x, int y, int z)
        {
            std::string code;

            code += "layout(";
            code += "local_size_x=" + std::to_string(x) + ",";
            code += "local_size_y=" + std::to_string(y) + ",";

            // TODO: figure out when you can exclude x/y/z
            if (z != 1)
                code += "local_size_z=" + std::to_string(z) + ")\n";

            code += "int main()\n{\n";

            return code;
        }

        static std::string closeMain()
        {
            return "}\n";
        }

        static std::string genUniforms(const std::vector<std::shared_ptr<Input>> inputs,
            const std::vector<std::shared_ptr<Output>> outputs)
        {
            std::string code;

            std::string name = "a";
            for (std::shared_ptr<Input> input : inputs)
            {
                code += "uniform " + input->getType() + " " + name + ";\n";
                input->name = name;
                updateName(name);
            }

            for (std::shared_ptr<Output> output : outputs)
            {
                code += "uniform " + output->getType() + " " + name + ";\n";
                output->name = name;
                updateName(name);
            }
            
            return code;
        }

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