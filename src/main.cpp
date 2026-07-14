#include <iostream>

#include "ance/Program.h"

int main(int const argc, char** argv)
{
    return ance::run(std::cout, std::cerr, argc, argv);
}
