#include "for_dump.h"


static void create_png        (int num);
static void graph_create_edge (Node* node, FILE* file);       
static void graph_create_point(Node* node, FILE* file);     


static void graph_create_point(Node* node, FILE* file)
{   
    if (node == NULL) return;

    if(node->left != NULL && node->right != NULL) fprintf(file, "POINT_%p[shape=Mrecord, label = \"%s?\", style=\"filled\",fillcolor=\"%s\"]\n", node, node->data, ELEM_TREE_COLOR);
    else                                          fprintf(file, "POINT_%p[shape=Mrecord, label = \"%s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node->data, SHEET_TREE_COLOR);

    graph_create_point(node->left, file);
    graph_create_point(node->right, file);
}   


static void graph_create_edge(Node* node, FILE* file) 
{   
    if (node == NULL) return;

    if (node->left) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->left);
    if (node->right) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->right);

    graph_create_edge(node->left, file);
    graph_create_edge(node->right, file);

}


static void create_png(int num)
{
    char command_create_png[200] = {};
    sprintf(command_create_png, "dot pictures/image%d%d.dot -Tpng -o pictures/pic%d%d.png", num / 10, num % 10, num / 10, num % 10);
    system(command_create_png);
}




void dump(Node* node, ForDump* st_dump) // рисует поддерево
{
    st_dump->dumps_counter++;
    int number_of_dump = st_dump->dumps_counter;

    char sample[] = "pictures/image00.dot";
    sample[14] = (char) ('0' + ((int) number_of_dump / 10));
    sample[15] = (char) ('0' + ((int) number_of_dump % 10));

    FILE* file = fopen(sample, "w");

    fprintf(file, "digraph\n{\nbgcolor=\"%s\";\nrankdir = TB;\n", FONT_COLOR);

    graph_create_point(node, file);

    graph_create_edge(node, file);

    fprintf(file, "}\n");

    fclose(file);

    create_png(number_of_dump);

}


void to_do_log_file(ForDump* st_dump)
{
    FILE* file = fopen(DUMP_FILE, "w");

    fprintf(file, "<pre>\n");
    fprintf(file, "<style>body {background-color:%s}</style>\n\n", FONT_COLOR);


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
