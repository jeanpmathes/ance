#ifndef ANCE_PROGRAM_H
#define ANCE_PROGRAM_H

#include <iosfwd>

namespace ance
{
    /// Run the ance compiler. The main method can directly invoke this.
    /// \param program_out The stream to output information from this program to. This is generally STDOUT, as it is output directly requested through options which might be used by subsequent tools.
    /// \param compiler_out The stream to output information about the performed compilation. This is generally STDERR, as it is helpful but not directly requested output.
    /// \param argc The number of program arguments.
    /// \param argv The array containing the program arguments.
    int run(std::ostream& program_out, std::ostream& compiler_out, int argc, char** argv);
}

#endif
