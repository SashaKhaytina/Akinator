// #include <stdio.h>
// #include <malloc.h>
// #include <stdlib.h>
// #include <string.h>


// #include "Stack/stack_commands.h"
// #include "Stack/errors.h"
// #include "Stack/utils.h"

// #include "akinator_h.h"
#include "game_options.h"
// #include "working_with_BD.h"
// #include "tree_commands.h"
// #include "for_dump.h"


// typedef char Node_t; // nfr


// const char* const ELEM_TREE_COLOR = "#D7CF8D";
// const char* const SHEET_TREE_COLOR = "#F9EA6B";
// const char* const FONT_COLOR = "#F2EECB";
// const char* const DUMP_FILE = "pictures/log.html";
// const size_t MAX_SIZE_TEXT_NODE = 200;
// const size_t MAX_DEEP_TREE = 30;
// const Node_t* FIRST_QUESTION = "It's alive?";
// const Node_t* FIRST_POSITIVE_ANS = "Person";
// const Node_t* FIRST_NEGATIVE_ANS = "Stone";

// const char* const CRITERIA_RIGHT = "YES";
// const char* const CRITERIA_LEFT = "NO";

// const char* const DATABASE = "tree.txt";


// enum StatusEndPlay
// {
//     LOSE,
//     WIN
// };

// enum BranchDirection
// {
//     RIGHT,
//     LEFT
// };

// struct Node
// {
//     Node_t data[MAX_SIZE_TEXT_NODE]; // Имя в ячейке
//     Node* left;
//     Node* right;
// };

// struct Tree
// {
//     Node* root;
// };

// struct ForDump
// {
//     char commands[100][30];
//     int dumps_counter;
// };


// void          init_tree         (Tree* tree);
// Node*         create_node       (const Node_t* data);
// Node*         add_new_node      (const Node_t* data); // perent - куда вставлять
// void          print_tree        (Node* node);         // при вызове тут должен ледать корень
// void          create_file_tree  (Tree* tree);
// void          print_tree_in_file(FILE* file, Node* node, size_t deep); 
// void          run_play          (Tree* tree);
// StatusEndPlay play_mystery      (Node* perent, Node** last_node);
// void          input_node_name   (char* arr);

// void create_png        (int num);
// void dump              (Node* node, ForDump* st_dump); // рисует поддерево
// void graph_create_edge (Node* node, FILE* file);       // при вызове тут должен лежать корень
// void graph_create_point(Node* node, FILE* file);       // при вызове тут должен лежать корень
// void to_do_log_file    (ForDump* st_dump);


// void definition           (Tree* tree, Node_t* object);
// bool bilding_way_to_object(Node* current_node, Node_t* object, Stack* stack, bool* found_object);



// size_t size_file(FILE* file);
// void get_tree(FILE* file, Tree* tree);
// void fill_tree(Node* current_node, int* i, char* arr_file_tree);
// void pass_spaces(int* i, char* arr_file_tree);
// void read_new_node(Node* current_node, int* i, char* arr_file_tree, BranchDirection line);





int main()
{
    start_game(); // Or create tree in main() better?

    // FILE* file = fopen(DATABASE, "r");

    // Tree tree = {};

    // ForDump st_dump = {};

    // get_tree(file, &tree);

    // run_play(&tree);
    // dump(tree.root, &st_dump);
    // create_file_tree(&tree);


    // run_play(&tree);
    // dump(tree.root, &st_dump);
    // create_file_tree(&tree);


    // char* c = "Howler";
    // definition(&tree, c);

    // c = "Albus Percival Wulfric Brian Dumbledore";
    // definition(&tree, c);

    // to_do_log_file(&st_dump);
}


// void init_tree(Tree* tree)
// {

//     tree->root = create_node(FIRST_QUESTION); // Это первая ячейка (вопрос)

//     tree->root->right = add_new_node(FIRST_POSITIVE_ANS);
//     tree->root->left  = add_new_node(FIRST_NEGATIVE_ANS);

// }


// Node* create_node(const Node_t* data)
// {
//     Node* new_node = (Node*) calloc(1, sizeof(Node));

//     strcpy(new_node->data, data);
//     new_node->left = NULL;
//     new_node->right = NULL;

//     return new_node;
// }

// Node* add_new_node(const Node_t* data) // perent - указатель куда вставлять (он может быть *Node.left ) (Причем сам Node.left = NULL)
// {

//     Node* new_node = create_node(data); 

//     return new_node;

// }




// void run_play(Tree* tree)
// {
//     Node* stop_play = NULL;
//     StatusEndPlay result = play_mystery(tree->root, &stop_play);


//     switch (result)
//     {
//         case WIN:
//         {
//             printf("I win!\n");
//             break;
//         }

//         case LOSE:
//         {
//             printf("I am loser :(\nWhat were you thinking about?\n"); // О ЧЕМ ТЫ ДУМАЛ????
//             char* new_data = NULL;
//             char input_data[MAX_SIZE_TEXT_NODE] = {};
//             input_node_name(input_data);
//             new_data = input_data;
            

//             printf("What is the difference?\n"); // Это должно даваться в форме: Акинатор угадал камень, а ты загадывал собаку. Чем отличается? ЭТО ЖИВОТНОЕ
//                                                  // То есть на написанный вопрос ответ должен быть ДА и мы получим новую ячейку (новая ячейка уходит вправо)
//             char* new_question = NULL;
//             char input_question[MAX_SIZE_TEXT_NODE] = {};
//             input_node_name(input_question);
//             new_question = input_question;

            
            
//             stop_play->right = add_new_node(new_data);
//             stop_play->left  = add_new_node(stop_play->data);

//             strcpy(stop_play->data, new_question); 
//             break;
//         }
    
//         default:
//         {
//             printf("ERROR. Frendship can't win here\n");
//             break;
//         }
//     }
// }



// void input_node_name(char* arr)
// {
//     char c = 0;
//     for (size_t i = 0; (((c = getchar()) != '\n') || (arr[0] == '\0')) && (i < MAX_SIZE_TEXT_NODE); i++) // как только ложь - завершиться
//     {
//         if (c == '\n'){i--; continue;}  
//         arr[i] = c;
//     }
// }



// StatusEndPlay play_mystery(Node* perent, Node** last_node)
// {
//     *last_node = perent;
//     printf("%s?\n", perent->data);
    
//     char* answer = NULL;
//     char vvod [200] = {};
//     scanf("%s", vvod);
//     answer = vvod;

//     while (true)
//     {
//         if (strcmp(answer, CRITERIA_RIGHT) == 0) 
//         {

//             if (perent->right == NULL) return WIN;
//             return play_mystery(perent->right, last_node);
//         }
//         else if (strcmp(answer, CRITERIA_LEFT) == 0)
//         {
//             if (perent->left == NULL) return LOSE;
//             return play_mystery(perent->left, last_node);
//         }
//         else
//         {
//             printf("It is wrong answer. Answer again:\n");
//             scanf("%s", vvod);
//             answer = vvod;
//         }
//     }
// }













// // ________________________________________________________________________________________________________________________________________________________
// // По чтению из файла - должна восстанавливать дерево. 
// // Как только встретилось } мы из этой ветки выходим. Иначе продолжаем вложенность. 
// // Можно читать без \t и без \n. Тогда будет большая строка чисто из названий (то есть "скобочная последовательность"). 


// size_t size_file(FILE* file)
// {
//     size_t size = 0;

//     fseek(file, 0, SEEK_END);
//     size = (size_t) ftell(file);
//     fseek(file, 0, SEEK_SET);

//     return size;
// }



// void get_tree(FILE* file, Tree* tree)
// {
//     size_t len_text = size_file(file);

//     // char arr_file_tree[(int) pow(2, MAX_DEEP_TREE) * MAX_SIZE_TEXT_NODE] = {}; // треш
//     char arr_file_tree[len_text] = {};

//     size_t count_symbol = fread(arr_file_tree, sizeof(char), len_text, file); // Прочитали. Тут есть и \t и \n и вообще каждый символ

//     int point_current_letter = 1;
//     // читаем имя (для root)
//     int ind_name = arr_file_tree[point_current_letter];
//     char name_root[MAX_SIZE_TEXT_NODE] = {};

//     // fgets(name_root, MAX_SIZE_TEXT_NODE, (arr_file_tree + point_current_letter));   // this function needs FILE*
//     while (arr_file_tree[point_current_letter] != '\n') // TODO: use standart function // which?(((
//     {
//         name_root[ind_name] = arr_file_tree[point_current_letter];
//         point_current_letter += 1;
//         ind_name++;
//     }

//     // создаем ячеку с этим именем
//     tree->root = create_node(name_root);
//     // printf("%s - name root\n", tree->root->data);

//     // for (int j = 0; j < 200; j++) printf("%c", arr_file_tree[j]);

//     fill_tree(tree->root, &point_current_letter, arr_file_tree);
// }


// void fill_tree(Node* current_node, int* point_current_letter, char* arr_file_tree) // TOD: rename i, сократи функцию
// {
//     pass_spaces(point_current_letter, arr_file_tree);

//     if (arr_file_tree[*point_current_letter] == '}') { *point_current_letter +=1; return; } 


//     if (arr_file_tree[*point_current_letter] == '{') // для левого поддерева
//     {
//         read_new_node(current_node, point_current_letter, arr_file_tree, LEFT);
//     }


//     pass_spaces(point_current_letter, arr_file_tree);


//     if (arr_file_tree[*point_current_letter] == '{') // для правого поддерева
//     {
//         read_new_node(current_node, point_current_letter, arr_file_tree, RIGHT);
//     }


//     pass_spaces(point_current_letter, arr_file_tree);

//     if (arr_file_tree[*point_current_letter] == '}') { *point_current_letter +=1; return; }

// }


// void pass_spaces(int* point_current_letter, char* arr_file_tree)
// {
//     while ((arr_file_tree[*point_current_letter] == '\t') || (arr_file_tree[*point_current_letter] == '\n') || (arr_file_tree[*point_current_letter] == ' ')) *point_current_letter += 1;
// }


// void read_new_node(Node* current_node, int* point_current_letter, char* arr_file_tree, BranchDirection line)
// {
//         *point_current_letter += 1;
//         // читаем имя
//         int ind_name = 0;
//         char name_node[MAX_SIZE_TEXT_NODE] = {};
//         while (arr_file_tree[*point_current_letter] != '\n')
//         {
//             name_node[ind_name] = arr_file_tree[*point_current_letter];
//             *point_current_letter += 1;
//             ind_name++;
//         }


//         // создаем ячеку с этим именем
//         Node* new_node = create_node(name_node);
//         if (line == RIGHT)
//         {
//             current_node->right = new_node;
//             fill_tree(current_node->right, point_current_letter, arr_file_tree);
//         }
//         else
//         {   
//             current_node->left = new_node;
//             fill_tree(current_node->left, point_current_letter, arr_file_tree);
//         }
// }


// //______________________________________________________________________________________________________________________________________________________________
































































// // Чтобы сравнить - все поделить по функциям, и вывод просто делать отдельно. А там массивы сравнить.

// void definition(Tree* tree, Node_t* object) // можно массив: [] (из да и нет) (А потом сверху восстановим)
// {
//     Stack stack = {};
//     default_stack_ctor(&stack, 32);

//     bool found_object = false;

//     found_object = bilding_way_to_object(tree->root, object, &stack, &found_object);

//     if (!found_object) printf("No this object in Tree\n");
//     else  // значит путь нашел
//     {
//         // тут надо вытаскивать путь из стека и по нему строить определение
//         size_t len_way = stack.size;

//         int way_to_object[MAX_DEEP_TREE] = {}; 
//         // 1) разворачиваем  -> получаем way_to_object
//         for (size_t i = 0; i < len_way; i++)
//         {
//             size_t current_size = stack.size;
//             StackElem_t pop_elem = 0;
//             stack_pop(&stack, &pop_elem);
//             way_to_object[current_size - 1] = (int) pop_elem;
//         }




//         // Читаю из массива путь
//         printf("Definition %s: ", object);
//         Node* current_node = tree->root;
//         for (size_t i = 0; i < len_way; i++)
//         {
//             if (way_to_object[i] == 1) // вправо
//             {
//                 printf("%s ", current_node->data);
//                 current_node = current_node->right;
//             }
//             else // влево
//             {
//                 printf("NO %s ", current_node->data);
//                 current_node = current_node->left;
//             }
//         }

//         printf("\n");
//     }
// }



// bool bilding_way_to_object(Node* current_node, Node_t* object, Stack* stack, bool* found_object)
// {
//     // проверить на нужность found_object
//     if (*found_object == true) return true;

//     if (strcmp(current_node->data, object) == 0)
//     {
//         *found_object = true;
//         return true;
//     }

//     if (current_node->right)
//     {
//         stack_push(stack, 1); // push 1 (вправо) 
//         if (bilding_way_to_object(current_node->right, object, stack, found_object)) return true;
//         else 
//         {
//             StackElem_t pop_elem = 0;
//             stack_pop(stack, &pop_elem); // pop
//         }
//     }
//     if (current_node->left)
//     {
//         stack_push(stack, 0); // push 0 (влево)
//         if (bilding_way_to_object(current_node->left, object, stack, found_object)) return true;
//         else 
//         {
//             StackElem_t pop_elem = 0;
//             stack_pop(stack, &pop_elem); // pop
//         }
//     }
//   return false;
    
// }








































































// void print_tree(Node* node) // при вызове тут должен лежать корень (с помощью этого можно делать вывод в файл)
// {   
//     if (node == NULL) return;

//     printf("(");
//     printf("%s", node->data);

//     print_tree(node->left);
//     print_tree(node->right);
//     printf(")");
//     // printf("\n");
// }


// void create_file_tree(Tree* tree)
// {
//     FILE* file = fopen(DATABASE, "w");

//     print_tree_in_file(file, tree->root, 0);

//     fclose(file);
// }

// void print_tree_in_file(FILE* file, Node* node, size_t deep) // при вызове тут должен лежать корень (можно поставить счетчик глубины (по нему колво tab делать. А в рекурсии запускать просто счетчик + 1)
// {   
//     char tabs[MAX_DEEP_TREE] = {}; // или можно назвать что-то типа current_deep
//     for (size_t i = 0; i < deep; i++) tabs[i] = '\t';
    
//     if (node == NULL) return;

//     fprintf(file, "%s{%s\n", tabs, node->data);
//     // fprintf(file, "\t%s%s\n", tabs, node->data);

//     print_tree_in_file(file, node->left, deep + 1);
//     print_tree_in_file(file, node->right, deep + 1);
//     fprintf(file, "%s}\n", tabs);
//     // printf("\n");
// }











































// void graph_create_point(Node* node, FILE* file) // при вызове тут должен лежать корень
// {   
//     // if (node == NULL) return;

//     // fprintf(file, "POINT_%p[shape=Mrecord, label = \"%s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node->data, ELEM_TREE_COLOR);

//     // graph_create_point(node->left, file);
//     // graph_create_point(node->right, file);

//     // это выглядит не очень (выше мне нравится больше), но зато тут звет и "?"

//     if (node == NULL) return;

//     if(node->left != NULL && node->right != NULL) fprintf(file, "POINT_%p[shape=Mrecord, label = \"%s?\", style=\"filled\",fillcolor=\"%s\"]\n", node, node->data, ELEM_TREE_COLOR);
//     else                                          fprintf(file, "POINT_%p[shape=Mrecord, label = \"%s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node->data, SHEET_TREE_COLOR);

//     graph_create_point(node->left, file);
//     graph_create_point(node->right, file);
// }   

// void graph_create_edge(Node* node, FILE* file) // при вызове тут должен лежать корень
// {   
//     if (node == NULL) return;

//     if (node->left) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->left);
//     if (node->right) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->right);

//     graph_create_edge(node->left, file);
//     graph_create_edge(node->right, file);

// }







// void dump(Node* node, ForDump* st_dump) // рисует поддерево
// {
//     st_dump->dumps_counter++;
//     int number_of_dump = st_dump->dumps_counter;

//     char sample[] = "pictures/image00.dot";
//     sample[14] = (char) ('0' + ((int) number_of_dump / 10));
//     sample[15] = (char) ('0' + ((int) number_of_dump % 10));

//     FILE* file = fopen(sample, "w");

//     fprintf(file, "digraph\n{\nbgcolor=\"%s\";\nrankdir = TB;\n", FONT_COLOR);

//     graph_create_point(node, file);

//     graph_create_edge(node, file);

//     fprintf(file, "}\n");

//     fclose(file);

//     create_png(number_of_dump);

// }


// void create_png(int num)
// {
//     char command_create_png[200] = {};
//     sprintf(command_create_png, "dot pictures/image%d%d.dot -Tpng -o pictures/pic%d%d.png", num / 10, num % 10, num / 10, num % 10);
//     system(command_create_png);
// }



// void to_do_log_file(ForDump* st_dump)
// {
//     FILE* file = fopen(DUMP_FILE, "w");

//     fprintf(file, "<pre>\n");
//     fprintf(file, "<style>body {background-color:%s}</style>\n\n", FONT_COLOR);


//     for (int i = 1; i <= st_dump->dumps_counter; i++)
//     {        
//         char sample[] = "pic00.png";
//         sample[3] = (char) ('0' + ((int) i / 10));
//         sample[4] = (char) ('0' + ((int) i % 10));

//         fprintf(file, "<big><big><div align=\"center\">Tree (print %d) &#128578;</div></big></big>\n\n", i); 

//         fprintf(file, "<div align=\"center\"><img src=\"%s\"></div>\n\n\n", sample);

//     }

//     fclose(file);
// }