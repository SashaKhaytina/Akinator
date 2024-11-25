#ifndef TREE_COMMANDS
#define TREE_COMMANDS

#include "akinator_h.h"

// const Node_t* FIRST_QUESTION     = "It's alive?";
// const Node_t* FIRST_POSITIVE_ANS = "Person";
// const Node_t* FIRST_NEGATIVE_ANS = "Stone";

void  init_tree         (Tree* tree);         // Only for NEW tree
Node* create_node       (const Node_t* data);
Node* add_new_node      (const Node_t* data); // perent - куда вставлять ЛМШНЯЯ ФУНКЦИЯ!!!!
void  print_tree        (Node* node);  


#endif