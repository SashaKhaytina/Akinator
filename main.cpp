#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef char Node_t; // nfr


const char* const ELEM_TREE_COLOR = "#AFEEEE";
const char* const DUMP_FILE = "pictures/log.html";
const size_t MAX_SIZE_TEXT_NODE = 200;
const size_t MAX_DEEP_TREE = 30;
const Node_t* FIRST_QUESTION = "It's alive?";
const Node_t* FIRST_POSITIVE_ANS = "Person";
const Node_t* FIRST_NEGATIVE_ANS = "Stone";

const char* const CRITERIA_RIGHT = "YES";
const char* const CRITERIA_LEFT = "NO";


enum StatusEndPlay
{
    LOSE,
    WIN
};

struct Node
{
    Node_t data[MAX_SIZE_TEXT_NODE]; // Имя в ячейке
    Node* left;
    Node* right;
};

struct Tree // это норм?
{
    Node* root;
};

struct ForDump
{
    char commands[100][30];
    int dumps_counter;
};


void init_tree(Tree* tree);
Node* create_node(const Node_t* data);
Node* add_new_node(const Node_t* data); // perent - куда вставлять
void print_tree(Node* node); // при вызове тут должен ледать корень
void print_file_tree(FILE* file, Node* node, size_t deep); 
void run_play(Tree* tree);
StatusEndPlay play_mystery(Node* perent, Node** last_node);

void create_png(int num);
void dump(Node* node, ForDump* st_dump); // рисует поддерево
void graph_create_edge(Node* node, FILE* file); // при вызове тут должен лежать корень
void graph_create_point(Node* node, FILE* file); // при вызове тут должен лежать корень
void to_do_log_file(ForDump* st_dump);






int main()
{

    FILE* file = fopen("tree.txt", "w");

    Tree tree = {};
    init_tree(&tree);

    ForDump st_dump = {};

    print_file_tree(file, tree.root, 0);

    dump(tree.root, &st_dump);
    print_tree(tree.root);
    printf("\n");
    run_play(&tree);
    printf("\n\n\n\n\n\n\n");
    print_file_tree(file, tree.root, 0);
    print_tree(tree.root);
    printf("\n");
    dump(tree.root, &st_dump);

    run_play(&tree);
    dump(tree.root, &st_dump);

    run_play(&tree);
    dump(tree.root, &st_dump);

    // add_new_node(50, tree.root);
    // dump(tree.root, &st_dump);

    // add_new_node(30, tree.root);
    // dump(tree.root, &st_dump);

    // add_new_node(70, tree.root);
    // dump(tree.root, &st_dump);

    // add_new_node(65, tree.root);
    // dump(tree.root, &st_dump);

    // add_new_node(10, tree.root);
    // dump(tree.root, &st_dump);

    // add_new_node(80, tree.root);
    // dump(tree.root, &st_dump);

    // to_do_log_file(&st_dump);
    // print_tree(tree.root);
    printf("\n");
}


void init_tree(Tree* tree)
{

    tree->root = create_node(FIRST_QUESTION); // Это первая ячейка (вопрос)
    // add_new_node(&tree->root->right, FIRST_POSITIVE_ANS);
    // add_new_node(&tree->root->left,  FIRST_NEGATIVE_ANS);

    tree->root->right = add_new_node(FIRST_POSITIVE_ANS);
    tree->root->left  = add_new_node(FIRST_NEGATIVE_ANS);

}


Node* create_node(const Node_t* data)
{
    // printf("Зашел в create_node\n");
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->data, data);
    new_node->left = NULL;
    new_node->right = NULL;

    // printf("GO out в create_node, %p\n", new_node);

    return new_node;
}

Node* add_new_node(const Node_t* data) // perent - указатель куда вставлять (он может быть *Node.left ) (Причем сам Node.left = NULL)
{
    // printf("%p", *perent);
    // char* data = {};
    // printf("What were you thinking about?\n");
    // scanf("%s", data);

    Node* new_node = create_node(data); // создали
    // printf("%p - new_node\n", new_node);                // положили

    return new_node;
    // printf("%p", *perent);


    // if (perent->data < data)
    // {
    //     if (perent->right != NULL) add_new_node(data, perent->right);
    //     else perent->right = create_node(data);
    // }

    // else
    // {
    //     if (perent->right != NULL) add_new_node(data, perent->left);
    //     else perent->left = create_node(data);
    // }

}




// АОАОАОА  один Segmentation fault (core dumped) за другим. За чтооооооооооооывтлытвлтылвтлытоттзукпукшпзукгпрваолпмвалдытиждлытерпдижлышщерджплыешщпждылпрщелдпршщыедлыепрщшептылетпжыетпыетпк

void run_play(Tree* tree)
{
    Node* stop_play = NULL;
    // printf("Start play\n");
    StatusEndPlay result = play_mystery(tree->root, &stop_play);
    // printf("stop-play - %p", stop_play);
    // printf("Stop play\n");

    switch (result)
    {
        case WIN:
        {
            printf("I win!\n");
            break;
        }

        case LOSE:
        {
            printf("I am loser :(\n What were you thinking about?\n"); // О ЧЕМ ТЫ ДУМАЛ????
            char* new_data = NULL;
            char vvod [200] = {};
            scanf("%s", vvod);
            new_data = vvod;
            

            printf("What is the difference?\n"); // Это должно даваться в форме: Акинатор угадал камень, а ты загадывал собаку. Чем отличается? ЭТО ЖИВОТНОЕ
                                                // То есть на написанный вопрос ответ должен быть ДА и мы получим новую ячейку (новая ячейка уходит вправо)
            char* new_question = NULL;
            char vvod2 [200] = {};
            scanf("%s", vvod2);
            new_question = vvod2;
            // printf("%p, %s\n", new_question, new_question);

            

            // add_new_node(&stop_play->right, new_data); // Это указатель на ответ который тут лежал. ЭТО ЛИСТИК
            // add_new_node(&stop_play->left, stop_play->data); // переместили листик
            // add_new_node(new_data);

            
            stop_play->right = add_new_node(new_data);
            // printf("ot do stop_play->right, neww - %p\n", stop_play->right);
            stop_play->left  = add_new_node(stop_play->data);

            strcpy(stop_play->data, new_question); // Добавить  вопросительный знак в конец
            // printf("NEW NAME: %s", stop_play->data);
            // printf("NEW NAME: %s", stop_play->right->data);
            // printf("NEW NAME: %s", stop_play->left->data);
            break;

        }

    
        default:
        {
            printf("ERROR. Frendship can't win here\n");
            break;
        }
    }
}




StatusEndPlay play_mystery(Node* perent, Node** last_node)
{
    // printf("Start func play\n");
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
            printf("It is wrong answer. Answer again:\n");
            scanf("%s", vvod);
            answer = vvod;
        }
    }
    

    // if (strcmp(answer, "YES") == 0) 
    // {
    //     // printf("he ans YES\n");
    //     if (perent->right == NULL) return WIN;
    //     return play_mystery(perent->right, last_node);
    // }

    // // printf("he ans NO\n");

    // if (perent->left == NULL) return LOSE;
    // return play_mystery(perent->left, last_node);
    

}












































































// void definition(Tree* tree, Node_t* object) // можно массив: [] (из да и нет) (А потом сверху восстановим)
// {
//     int way_to_object[MAX_DEEP_TREE] = {}; 
//     for (size_t i = 0; i < MAX_DEEP_TREE; i++) way_to_object[i] = -1;

//     bool found_object = false;

//     found_object = bilding_way_to_object(tree->root, object, way_to_object, &found_object);

//     if (!found_object) printf("No this object in Tree\n");
//     else  // значит путь нашел
//     {
//         // тут надо вытаскивать путь из стека и по нему строить определение
//         // запомним size стека
//         int size = 0;
//         // int way_to_object[MAX_DEEP_TREE] = {}; 
//         // 1) разворачиваем  -> получаем way_to_object
//         Node* current_node = tree->root;
//         for (int i = 0; i < size; i++)
//         {
//             if (way_to_object[i] == 1) // вправо
//             {
//                 printf("%s ", current_node->data);
//                 current_node = current_node->right;
//             }
//             else
//             {
//                 printf("NO %s ", current_node->data);
//                 current_node = current_node->left;
//             }
//         }
//     }
// }



// bool bilding_way_to_object(Node* current_node, Node_t* object, int* way_to_object, bool* found_object)
// {
//     // if (strcmp(current_node->data, object) == 0)
//     // Поставим переменную-датчик (дошли мы до этой ячейки или нет)
//     if (*found_object == true) return;

//     if (strcmp(current_node->data, object) == 0)
//     {
//         *found_object = true;
//         return;
//     }

//     if (current_node->right)
//     {
//         // push 1 (вправо)
//         if (bilding_way_to_object(current_node->right, object, way_to_object, found_object)) return true;
//         else ; // pop
//     }
//     if (current_node->left)
//     {
//         // push 0 (влево)
//         if (bilding_way_to_object(current_node->left, object, way_to_object, found_object)) return true;
//         else ; // pop
//     }

//     return false;
    
// }








































































void print_tree(Node* node) // при вызове тут должен лежать корень (с помощью этого можно делать вывод в файл)
{   
    if (node == NULL) return;

    printf("(");
    printf("%s", node->data);

    print_tree(node->left);
    print_tree(node->right);
    printf(")");
    // printf("\n");
}


void print_file_tree(FILE* file, Node* node, size_t deep) // при вызове тут должен лежать корень (можно поставить счетчик глубины (по нему колво tab делать. А в рекурсии запускать просто счетчик + 1)
{   
    // FILE* file = fopen("tree.txt", "w");

    char tabs[MAX_DEEP_TREE] = {}; // или можно назвать что-то типа current_deep
    for (size_t i = 0; i < deep; i++) tabs[i] = '\t';
    
    if (node == NULL) return;

    fprintf(file, "%s{\n", tabs);
    fprintf(file, "\t%s%s\n", tabs, node->data);

    print_file_tree(file, node->left, deep + 1);
    print_file_tree(file, node->right, deep + 1);
    fprintf(file, "%s}\n", tabs);
    // printf("\n");
}











































void graph_create_point(Node* node, FILE* file) // при вызове тут должен лежать корень
{   
    if (node == NULL) return;


    // printf("%d", node->data);
    fprintf(file, "POINT_%p[shape=Mrecord, label = \"%s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node->data, ELEM_TREE_COLOR);

    graph_create_point(node->left, file);
    graph_create_point(node->right, file);
}

void graph_create_edge(Node* node, FILE* file) // при вызове тут должен лежать корень
{   
    if (node == NULL) return;

    if (node->left) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->left);
    if (node->right) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->right);

    graph_create_edge(node->left, file);
    graph_create_edge(node->right, file);

}







void dump(Node* node, ForDump* st_dump) // рисует поддерево
{
    st_dump->dumps_counter++;
    int number_of_dump = st_dump->dumps_counter;

    char sample[] = "pictures/image00.dot";
    sample[14] = (char) ('0' + ((int) number_of_dump / 10));
    sample[15] = (char) ('0' + ((int) number_of_dump % 10));
    // printf("%s - sample\n", sample);
    FILE* file = fopen(sample, "w");

    fprintf(file, "digraph\n{\nrankdir = TB;\n");

    graph_create_point(node, file);

    graph_create_edge(node, file);

    fprintf(file, "}\n");

    fclose(file);

    create_png(number_of_dump);

}


void create_png(int num)
{
    char command_create_png[200] = {};
    sprintf(command_create_png, "dot pictures/image%d%d.dot -Tpng -o pictures/pic%d%d.png", num / 10, num % 10, num / 10, num % 10);
    system(command_create_png);
}



void to_do_log_file(ForDump* st_dump)
{
    FILE* file = fopen(DUMP_FILE, "w");

    fprintf(file, "<pre>\n");

    for (int i = 1; i <= st_dump->dumps_counter; i++)
    {        
        char sample[] = "pic00.png";
        sample[3] = (char) ('0' + ((int) i / 10));
        sample[4] = (char) ('0' + ((int) i % 10));

        fprintf(file, "<big><big><div align=\"center\">Tree (print %d) &#128578;</div></big></big>\n\n", i); 

        fprintf(file, "<div align=\"center\"><img src=\"%s\"></div>\n\n\n", sample);

    }

    fclose(file);
}