#include "game_options.h"

#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

#include "tree_commands.h"
#include "working_with_BD.h"
#include "for_dump.h"

#include <string.h>





static void          help_mode      ();
static void          definition_mode(Tree* tree);
static void          mystery_mode   (Tree* tree, ForDump* st_dump);

static void          run_play             (Tree* tree);
static StatusEndPlay play_mystery         (Node* perent, Node** last_node);
static void          input_node_name      (char* arr);
static void          definition           (Tree* tree, Node_t* object);
static bool          bilding_way_to_object(Node* current_node, Node_t* object, Stack* stack, bool* found_object);







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

    char c = 0;
    int ind = 0;
    c = getchar();
    while ((c = getchar()) != '\n')
    {
        word[ind] = c;
        ind++;
    }

    definition(tree, word);

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

            
            
            stop_play->right = add_new_node(new_data);
            stop_play->left  = add_new_node(stop_play->data);

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

static void definition(Tree* tree, Node_t* object) // массив: [] (из да и нет) (А потом сверху восстановим)
{
    Stack stack = {};
    default_stack_ctor(&stack, 32);

    bool found_object = false;

    found_object = bilding_way_to_object(tree->root, object, &stack, &found_object);

    if (!found_object) PRINTF_BLUE("No this object in Tree\n");
    else  // значит путь нашел
    {
        size_t len_way = stack.size;

        int way_to_object[MAX_DEEP_TREE] = {}; 

        for (size_t i = 0; i < len_way; i++)
        {
            size_t current_size = stack.size;
            StackElem_t pop_elem = 0;
            stack_pop(&stack, &pop_elem);
            way_to_object[current_size - 1] = (int) pop_elem;
        }


        PRINTF_GREEN("Definition %s: ", object);
        Node* current_node = tree->root;
        for (size_t i = 0; i < len_way; i++)
        {
            if (way_to_object[i] == 1) // вправо
            {
                printf("%s. ", current_node->data);
                current_node = current_node->right;
            }
            else // влево
            {
                printf("NO %s. ", current_node->data);
                current_node = current_node->left;
            }
        }

        printf("\n");
    }
}



static bool bilding_way_to_object(Node* current_node, Node_t* object, Stack* stack, bool* found_object)
{
    // проверить на нужность found_object
    if (*found_object == true) return true;

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
