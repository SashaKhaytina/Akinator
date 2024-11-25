#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>

typedef char Node_t; 

const size_t MAX_SIZE_TEXT_NODE = 200;
const size_t MAX_DEEP_TREE      = 30;
const char* const DATABASE      = "tree.txt";


struct Node
{
    Node_t data[MAX_SIZE_TEXT_NODE]; 
    Node* left;
    Node* right;
};

struct Tree
{
    Node* root;
};

struct ForDump
{
    char commands[100][30];
    int dumps_counter;
};

#endif