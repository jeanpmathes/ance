#include <filesystem>
#include <iostream>

#include <boost/locale.hpp>

static int ance(const int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "ance: command: Requires exactly one argument" << std::endl;
        return EXIT_FAILURE;
    }

    boost::locale::generator const gen;
    std::locale const              loc = gen("");
    std::locale::global(loc);

    std::filesystem::path file_path(argv[1]);
    if (file_path.is_relative()) file_path = absolute(file_path);
    if (!exists(file_path))
    {
        std::cout << "ance: input: File does not exist" << std::endl;
        return EXIT_FAILURE;
    }

    bool const ok = true;

    // todo: create the runner and parser and the intermediate steps
    // todo: parse the file
    // todo: do the intermediate steps
    // todo: give it to the runner

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(int const argc, char** argv)
{
    try
    {
        return ance(argc, argv);
    }
    catch (std::exception const& e)
    {
        std::cerr << "ance: internal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
