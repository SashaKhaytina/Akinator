#ifndef WORKING_WITH_BD
#define WORKING_WITH_BD

#include "akinator_h.h"



enum BranchDirection
{
    RIGHT,
    LEFT
};

void   get_tree(FILE* file, Tree* tree);
void   create_file_tree  (Tree* tree);
// size_t size_file(FILE* file);
// void   fill_tree(Node* current_node, int* i, char* arr_file_tree);
// void   pass_spaces(int* i, char* arr_file_tree);
// void   read_new_node(Node* current_node, int* i, char* arr_file_tree, BranchDirection line);
// void   print_tree_in_file(FILE* file, Node* node, size_t deep); 


#endif