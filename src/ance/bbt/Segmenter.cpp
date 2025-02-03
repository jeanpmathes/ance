#include "Segmenter.h"

struct ance::bbt::Segmenter::Implementation
{

};

ance::bbt::Segmenter::Segmenter() : implementation_(utility::makeOwned<Implementation>()) {}

ance::bbt::Segmenter::~Segmenter() = default;
