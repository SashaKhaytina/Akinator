#ifndef WORKING_WITH_BD
#define WORKING_WITH_BD

#include "akinator_h.h"



enum BranchDirection
{
    RIGHT,
    LEFT
};

void get_tree(FILE* file, Tree* tree);
void create_file_tree  (Tree* tree);


#endif