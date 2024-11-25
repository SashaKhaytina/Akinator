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


static void fill_tree(Node* current_node, int* point_current_letter, char* arr_file_tree) // TOD: rename i, сократи функцию
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
        // читаем имя
        int ind_name = 0;
        char name_node[MAX_SIZE_TEXT_NODE] = {};
        while (arr_file_tree[*point_current_letter] != '\n')
        {
            name_node[ind_name] = arr_file_tree[*point_current_letter];
            *point_current_letter += 1;
            ind_name++;
        }


        // создаем ячеку с этим именем
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


static void print_tree_in_file(FILE* file, Node* node, size_t deep) // при вызове тут должен лежать корень (можно поставить счетчик глубины (по нему колво tab делать. А в рекурсии запускать просто счетчик + 1)
{   
    char tabs[MAX_DEEP_TREE] = {}; // или можно назвать что-то типа current_deep
    for (size_t i = 0; i < deep; i++) tabs[i] = '\t';
    
    if (node == NULL) return;

    fprintf(file, "%s{%s\n", tabs, node->data);
    // fprintf(file, "\t%s%s\n", tabs, node->data);

    print_tree_in_file(file, node->left, deep + 1);
    print_tree_in_file(file, node->right, deep + 1);
    fprintf(file, "%s}\n", tabs);
    // printf("\n");
}




void get_tree(FILE* file, Tree* tree)
{
    size_t len_text = size_file(file);

    // char arr_file_tree[(int) pow(2, MAX_DEEP_TREE) * MAX_SIZE_TEXT_NODE] = {}; // треш
    char arr_file_tree[len_text] = {};

    size_t count_symbol = fread(arr_file_tree, sizeof(char), len_text, file); // Прочитали. Тут есть и \t и \n и вообще каждый символ

    int point_current_letter = 1;
    // читаем имя (для root)
    // int ind_name = arr_file_tree[point_current_letter];
    int ind_name = 0;
    char name_root[MAX_SIZE_TEXT_NODE] = {};

    // fgets(name_root, MAX_SIZE_TEXT_NODE, (arr_file_tree + point_current_letter));   // this function needs FILE*
    while (arr_file_tree[point_current_letter] != '\n') // TODO: use standart function // which?(((
    {
        name_root[ind_name] = arr_file_tree[point_current_letter];
        point_current_letter += 1;
        ind_name++;
    }

    // создаем ячеку с этим именем
    tree->root = create_node(name_root);
    // printf("%s - name root\n", tree->root->data);

    // for (int j = 0; j < 200; j++) printf("%c", arr_file_tree[j]);

    fill_tree(tree->root, &point_current_letter, arr_file_tree);
}


void create_file_tree(Tree* tree)
{
    FILE* file = fopen(DATABASE, "w");

    print_tree_in_file(file, tree->root, 0);

    fclose(file);
}
