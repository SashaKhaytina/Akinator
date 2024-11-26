#include "tree_commands.h"
#include <malloc.h>
#include <string.h>

// Why error, when it in tree_commands.h?
const Node_t* FIRST_QUESTION     = "It's alive?";
const Node_t* FIRST_POSITIVE_ANS = "Person";
const Node_t* FIRST_NEGATIVE_ANS = "Stone";

void init_tree(Tree* tree)
{

    tree->root = create_node(FIRST_QUESTION); // Это первая ячейка (вопрос)

    tree->root->right = create_node(FIRST_POSITIVE_ANS);
    tree->root->left  = create_node(FIRST_NEGATIVE_ANS);

}


Node* create_node(const Node_t* data)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->data, data);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}


void print_tree(Node* node)
{   
    if (node == NULL) return;

    printf("(");
    printf("%s", node->data);

    print_tree(node->left);
    print_tree(node->right);
    printf(")");
}
