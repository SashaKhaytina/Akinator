#ifndef TREE_COMMANDS
#define TREE_COMMANDS

#include "akinator_h.h"

// const Node_t* FIRST_QUESTION     = "It's alive?";
// const Node_t* FIRST_POSITIVE_ANS = "Person";
// const Node_t* FIRST_NEGATIVE_ANS = "Stone";



void  init_tree  (Tree* tree);         // Only for NEW tree
Node* create_node(const Node_t* data);
void  print_tree (Node* node);  


#endif