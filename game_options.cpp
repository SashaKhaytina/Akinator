#include "game_options.h"

#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

#include "tree_commands.h"
#include "working_with_BD.h"
#include "for_dump.h"
#include "utils.h"

#include <string.h>





static void          help_mode      ();
static void          definition_mode(Tree* tree);
static void          mystery_mode   (Tree* tree, ForDump* st_dump);
static void          comparison_mode(Tree* tree);

static void          run_play             (Tree* tree);
static StatusEndPlay play_mystery         (Node* perent, Node** last_node);
static void          input_node_name      (char* arr);
static void          definition           (Tree* tree, Node_t* object);
static void          comparison           (Tree* tree, Node_t* object1, Node_t* object2);
static bool          bilding_way_to_object(Node* current_node, Node_t* object, Stack* stack, bool* found_object);
static void          get_way_array        (int* way_to_object, Stack* stack);
static void          characteristic_node  (Node** current_node, int* way_to_object, int current_deep);







void start_game()
{
    PRINTF_BLUE("Hello!\n");

    FILE* file = fopen(DATABASE, "r");
    Tree tree = {};
    ForDump st_dump = {};

    get_tree(file, &tree);

    while (true)
    {
        PRINTF_BLUE("Choose mode! (If you don't know modes, write "); PRINTF_GREEN("\"help\""); PRINTF_BLUE("):\n");

        char command[30];
        scanf("%s", command);

        if      (strcmp(command, "help")       == 0) help_mode();
        else if (strcmp(command, "definition") == 0) definition_mode(&tree);
        else if (strcmp(command, "mystery")    == 0) mystery_mode(&tree, &st_dump);
        else if (strcmp(command, "comparison") == 0) comparison_mode(&tree);

        else if (strcmp(command, "END")    == 0) break;

        else PRINTF_RED("Error command. Write command again\n");

    }
    to_do_log_file(&st_dump);
}




static void help_mode()
{
    printf("\n");
    PRINTF_YELLOW("Write "); PRINTF_GREEN("\"definition\""); PRINTF_YELLOW(" if you want to know word definition\n");
    
    PRINTF_YELLOW("Write "); PRINTF_GREEN("\"mystery\""); PRINTF_YELLOW(" if you want guess the word\n");

    PRINTF_YELLOW("Write "); PRINTF_GREEN("\"END\""); PRINTF_YELLOW(" if you want end programm\n");

    printf("\n");
}


static void definition_mode(Tree* tree)
{
    char word[MAX_SIZE_TEXT_NODE] = {};
    PRINTF_BLUE("Write your word\n");

    input_node_name(word);

    // char c = 0;
    // int ind = 0;
    // c = getchar();
    // while ((c = getchar()) != '\n')
    // {
    //     word[ind] = c;
    //     ind++;
    // }

    definition(tree, word);

}


static void comparison_mode(Tree* tree)
{
    char word1[MAX_SIZE_TEXT_NODE] = {};
    char word2[MAX_SIZE_TEXT_NODE] = {};
    char c = 0;

    PRINTF_BLUE("Write your first word\n");
    input_node_name(word1);
    // printf("%s", word1);
    // c = getchar();
    // int ind = 0;
    // while ((c = getchar()) != '\n')
    // {
    //     word1[ind] = c;
    //     ind++;
    // }

    PRINTF_BLUE("Write your second word\n");
    input_node_name(word2);
    // ind = 0;
    // while ((c = getchar()) != '\n')
    // {
    //     word2[ind] = c;
    //     ind++;
    // }


    comparison(tree, word1, word2);
}


static void mystery_mode(Tree* tree, ForDump* st_dump)
{
    run_play(tree);
    dump(tree->root, st_dump);
    create_file_tree(tree);
}


static void run_play(Tree* tree)
{
    Node* stop_play = NULL;
    StatusEndPlay result = play_mystery(tree->root, &stop_play);


    switch (result)
    {
        case WIN:
        {
            PRINTF_GREEN("I win!\n");
            break;
        }

        case LOSE:
        {
            PRINTF_RED("I am loser :(\n"); PRINTF_BLUE("What were you thinking about?\n"); // О ЧЕМ ТЫ ДУМАЛ????
            char* new_data = NULL;
            char input_data[MAX_SIZE_TEXT_NODE] = {};
            input_node_name(input_data);
            new_data = input_data;
            

            PRINTF_BLUE("What is the difference?\n");

            char* new_question = NULL;
            char input_question[MAX_SIZE_TEXT_NODE] = {};
            input_node_name(input_question);
            new_question = input_question;

            
            
            stop_play->right = create_node(new_data);
            stop_play->left  = create_node(stop_play->data);

            strcpy(stop_play->data, new_question); 
            break;
        }
    
        default:
        {
            PRINTF_RED("ERROR. Frendship can't win here\n");
            break;
        }
    }
}



static void input_node_name(char* arr)
{
    char c = 0;
    for (size_t i = 0; (((c = getchar()) != '\n') || (arr[0] == '\0')) && (i < MAX_SIZE_TEXT_NODE); i++) 
    {
        if (c == '\n'){i--; continue;}  
        arr[i] = c;
    }
}



static StatusEndPlay play_mystery(Node* perent, Node** last_node)
{
    *last_node = perent;
    printf("%s?\n", perent->data);
    
    char* answer = NULL;
    char vvod [200] = {};
    scanf("%s", vvod);
    answer = vvod;

    while (true)
    {
        if (strcmp(answer, CRITERIA_RIGHT) == 0) 
        {

            if (perent->right == NULL) return WIN;
            return play_mystery(perent->right, last_node);
        }
        else if (strcmp(answer, CRITERIA_LEFT) == 0)
        {
            if (perent->left == NULL) return LOSE;
            return play_mystery(perent->left, last_node);
        }
        else
        {
            PRINTF_RED("It is wrong answer. Answer again:\n");
            scanf("%s", vvod);
            answer = vvod;
        }
    }
}


// Чтобы сравнить - все поделить по функциям, и вывод просто делать отдельно. А там массивы сравнить.

static void comparison(Tree* tree, Node_t* object1, Node_t* object2)
{
    // To do func for this is stange
    Stack stack1 = {}; default_stack_ctor(&stack1, MAX_DEEP_TREE);
    Stack stack2 = {}; default_stack_ctor(&stack2, MAX_DEEP_TREE);

    bool found_object1 = false;
    bool found_object2 = false;
    found_object1 = bilding_way_to_object(tree->root, object1, &stack1, &found_object1);
    found_object2 = bilding_way_to_object(tree->root, object2, &stack2, &found_object2);

    // Why not?
    // bool found_object1 = bilding_way_to_object(tree->root, object1, &stack1, &found_object1);
    // bool found_object2 = bilding_way_to_object(tree->root, object2, &stack2, &found_object2);

    if (!found_object1) { PRINTF_RED("No %s in Tree\n", object1); return; }
    if (!found_object2) { PRINTF_RED("No %s in Tree\n", object2); return; }

    int way_to_object1[MAX_DEEP_TREE] = {};
    int way_to_object2[MAX_DEEP_TREE] = {};

    size_t len_way1 = stack1.size;
    size_t len_way2 = stack2.size;

    get_way_array(way_to_object1, &stack1);
    get_way_array(way_to_object2, &stack2);

    Node* current_node = tree->root;

    PRINTF_MAGENTA("%s and %s BOTH ", object1, object2);

    for (int i = 0; i < min(len_way1, len_way2); i++)
    {
        if (way_to_object1[i] != way_to_object2[i])
        {
            PRINTF_MAGENTA("BUT %s ", object1);

            characteristic_node(&current_node, way_to_object1, i);
            printf("\n");
            return; // only 1 different

            // if (way_to_object1[i] == 1) // вправо
            // {
            //     printf("%s. ", current_node->data);
            //     current_node = current_node->right;
            // }
            // else // влево
            // {
            //     printf("NO %s. ", current_node->data);
            //     current_node = current_node->left;
            // }
        }

        characteristic_node(&current_node, way_to_object1, i);

        // if (way_to_object1[i] == 1) // вправо
        // {
        //     printf("%s. ", current_node->data);
        //     current_node = current_node->right;
        // }
        // else // влево
        // {
        //     printf("NO %s. ", current_node->data);
        //     current_node = current_node->left;
        // }
    }
    printf("\n");
    stack_dtor(&stack1);
    stack_dtor(&stack2);
}




static void definition(Tree* tree, Node_t* object) // массив: [] (из да и нет) (А потом сверху восстановим)
{
    Stack stack = {}; default_stack_ctor(&stack, MAX_DEEP_TREE);

    bool found_object = false;
    found_object = bilding_way_to_object(tree->root, object, &stack, &found_object);

    if (!found_object) PRINTF_BLUE("No this object in Tree\n");
    else  // значит путь нашел
    {
        int way_to_object[MAX_DEEP_TREE] = {}; 
        size_t len_way = stack.size;

        get_way_array(way_to_object, &stack);


        // for (size_t i = 0; i < len_way; i++)
        // {
        //     size_t current_size = stack.size;
        //     StackElem_t pop_elem = 0;
        //     stack_pop(&stack, &pop_elem);
        //     way_to_object[current_size - 1] = (int) pop_elem;
        // }


        PRINTF_GREEN("Definition %s: ", object);
        Node* current_node = tree->root;
        for (size_t i = 0; i < len_way; i++)
        {
            characteristic_node(&current_node, way_to_object, i);

            // if (way_to_object[i] == 1) // вправо
            // {
            //     printf("%s. ", current_node->data);
            //     current_node = current_node->right;
            // }
            // else // влево
            // {
            //     printf("NO %s. ", current_node->data);
            //     current_node = current_node->left;
            // }
        }

        printf("\n");
    }
    stack_dtor(&stack);
}

static void get_way_array(int* way_to_object, Stack* stack)
{
    size_t len_way = stack->size;

    for (size_t i = 0; i < len_way; i++)
    {
        size_t current_size = stack->size;
        StackElem_t pop_elem = 0;
        stack_pop(stack, &pop_elem);
        way_to_object[current_size - 1] = (int) pop_elem;
    }
}

static void characteristic_node(Node** current_node, int* way_to_object, int current_deep)
{
    // Is this needs checking? (for way_to_object[current_deep]) 

    if (way_to_object[current_deep] == 1) // вправо
    {
        printf("%s. ", (*current_node)->data);
        *current_node = (*current_node)->right;
    }
    else // влево
    {
        printf("NO %s. ", (*current_node)->data);
        *current_node = (*current_node)->left;
    }
}
// bool found_way(Tree* tree, Node_t* object, Stack* stack)
// {
//     bool found_object = false;

//     found_object = bilding_way_to_object(tree->root, object, stack, &found_object);
   
// }


static bool bilding_way_to_object(Node* current_node, Node_t* object, Stack* stack, bool* found_object)
{
    // проверить на нужность found_object
    if (*found_object == true) {printf("aaaaaaaaaaaaaaaaaa"); return true;}

    if (strcmp(current_node->data, object) == 0)
    {
        *found_object = true;
        return true;
    }

    if (current_node->right)
    {
        stack_push(stack, 1); // push 1 (вправо) 
        if (bilding_way_to_object(current_node->right, object, stack, found_object)) return true;
        else 
        {
            StackElem_t pop_elem = 0;
            stack_pop(stack, &pop_elem); // pop
        }
    }
    if (current_node->left)
    {
        stack_push(stack, 0); // push 0 (влево)
        if (bilding_way_to_object(current_node->left, object, stack, found_object)) return true;
        else 
        {
            StackElem_t pop_elem = 0;
            stack_pop(stack, &pop_elem); // pop
        }
    }
  return false;
    
}
