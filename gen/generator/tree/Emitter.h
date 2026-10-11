#ifndef TREE_EMITTER_H
#define TREE_EMITTER_H

#include "tree/Model.h"

#include <string>

namespace tree
{
    std::string generateHeader(Model const& model);
    std::string generateSource(Model const& model, std::string const& include_path);
}

#endif
