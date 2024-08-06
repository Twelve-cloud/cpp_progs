#ifndef CODE_DECODER_H
#define CODE_DECODER_H

#include <iostream>
#include <fstream>
#include <string>

bool decode(int argc, char* argv[])
{
    if (argc == 1)
    {
        return false
    }
    else
    {
        std::string buffer, tmp;
        for (size_t i = 1; i < argc; i++)
        {
            std::cout << "Program " << i << std::endl;
            std::fstream fs(argv[i]);
            while (!fs.eof())
            {
                std::getline(fs, tmp);
                buffer += tmp += '\n';
            }
            std::cout << buffer;
            buffer.clear();
            fs.close();
        }
    }

    return true;
}

#endif // CODE_DECODER_H
