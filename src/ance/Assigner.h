#ifndef ANCE_SRC_ANCE_ASSIGNER_H_
#define ANCE_SRC_ANCE_ASSIGNER_H_

enum class Assigner
{
    COPY_ASSIGNMENT,
    MOVE_ASSIGNMENT,
    FINAL_COPY_ASSIGNMENT
};

bool IsFinal(Assigner assigner);

#endif
