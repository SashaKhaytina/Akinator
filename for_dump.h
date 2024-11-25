#ifndef FOR_DUMP
#define FOR_DUMP

#include "akinator_h.h"
#include <stdlib.h>

const char* const ELEM_TREE_COLOR  = "#D7CF8D";
const char* const SHEET_TREE_COLOR = "#F9EA6B";
const char* const FONT_COLOR       = "#F2EECB";
const char* const DUMP_FILE        = "pictures/log.html";


void dump              (Node* node, ForDump* st_dump); // рисует поддерево
void to_do_log_file    (ForDump* st_dump);
// void create_png        (int num);
// void graph_create_edge (Node* node, FILE* file);       // при вызове тут должен лежать корень
// void graph_create_point(Node* node, FILE* file);       // при вызове тут должен лежать корень



#endif