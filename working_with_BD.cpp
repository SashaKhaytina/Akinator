#include "working_with_BD.h"
#include "tree_commands.h"


static size_t size_file(FILE* file);
static void   fill_tree(Node* current_node, int* i, char* arr_file_tree);
static void   pass_spaces(int* i, char* arr_file_tree);
static void   read_new_node(Node* current_node, int* i, char* arr_file_tree, BranchDirection line);
static void   print_tree_in_file(FILE* file, Node* node, size_t deep); 



static size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}


static void fill_tree(Node* current_node, int* point_current_letter, char* arr_file_tree)
{
    pass_spaces(point_current_letter, arr_file_tree);

    if (arr_file_tree[*point_current_letter] == '}') { *point_current_letter +=1; return; } 


    if (arr_file_tree[*point_current_letter] == '{') // для левого поддерева
    {
        read_new_node(current_node, point_current_letter, arr_file_tree, LEFT);
    }


    pass_spaces(point_current_letter, arr_file_tree);


    if (arr_file_tree[*point_current_letter] == '{') // для правого поддерева
    {
        read_new_node(current_node, point_current_letter, arr_file_tree, RIGHT);
    }


    pass_spaces(point_current_letter, arr_file_tree);

    if (arr_file_tree[*point_current_letter] == '}') { *point_current_letter +=1; return; }

}


static void pass_spaces(int* point_current_letter, char* arr_file_tree)
{
    while ((arr_file_tree[*point_current_letter] == '\t') || (arr_file_tree[*point_current_letter] == '\n') || (arr_file_tree[*point_current_letter] == ' ')) *point_current_letter += 1;
}


static void read_new_node(Node* current_node, int* point_current_letter, char* arr_file_tree, BranchDirection line)
{
        *point_current_letter += 1;

        int ind_name = 0;
        char name_node[MAX_SIZE_TEXT_NODE] = {};
        while (arr_file_tree[*point_current_letter] != '\n')
        {
            name_node[ind_name] = arr_file_tree[*point_current_letter];
            *point_current_letter += 1;
            ind_name++;
        }

        Node* new_node = create_node(name_node);
        if (line == RIGHT)
        {
            current_node->right = new_node;
            fill_tree(current_node->right, point_current_letter, arr_file_tree);
        }
        else
        {   
            current_node->left = new_node;
            fill_tree(current_node->left, point_current_letter, arr_file_tree);
        }
}


static void print_tree_in_file(FILE* file, Node* node, size_t deep)
{   
    char tabs[MAX_DEEP_TREE] = {};
    for (size_t i = 0; i < deep; i++) tabs[i] = '\t';
    
    if (node == NULL) return;

    fprintf(file, "%s{%s\n", tabs, node->data);

    print_tree_in_file(file, node->left, deep + 1);
    print_tree_in_file(file, node->right, deep + 1);
    fprintf(file, "%s}\n", tabs);
}


void get_tree(FILE* file, Tree* tree)
{
    size_t len_text = size_file(file);

    char arr_file_tree[len_text] = {};

    size_t count_symbol = fread(arr_file_tree, sizeof(char), len_text, file);

    int point_current_letter = 1;

    int ind_name = 0;
    char name_root[MAX_SIZE_TEXT_NODE] = {};

    // fgets(name_root, MAX_SIZE_TEXT_NODE, (arr_file_tree + point_current_letter));   // this function needs FILE*
    while (arr_file_tree[point_current_letter] != '\n') // TODO: use standart function // which?(((
    {
        name_root[ind_name] = arr_file_tree[point_current_letter];
        point_current_letter += 1;
        ind_name++;
    }

    tree->root = create_node(name_root);

    fill_tree(tree->root, &point_current_letter, arr_file_tree);
}


void create_file_tree(Tree* tree)
{
    FILE* file = fopen(DATABASE, "w");

    print_tree_in_file(file, tree->root, 0);

    fclose(file);
}
