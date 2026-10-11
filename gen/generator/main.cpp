#include "Definition.h"
#include "DefinitionRegistry.h"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>

int main(int const argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ance_generator <output-directory>\n";
        return EXIT_FAILURE;
    }

    std::filesystem::path const output_root = argv[1];

    std::ranges::for_each(
        DefinitionRegistry::getDefinitions(),
        [&output_root](Definition const* const definition) {
            definition->generate(output_root);
        }
    );

    return EXIT_SUCCESS;
}
