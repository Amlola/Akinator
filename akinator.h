#pragma once


#include "tree.h"
#include "stack.h"



enum FindHero 
    {
    HERO_IS_NOT_FOUND = 0,
    HERO_IS_FOUND     = 1
    };

const size_t MAX_STRING_LEN = 100;

const size_t MAX_LEN_ANS = 100;


void Game(Tree* tree, FILE* data_base, Text* data);


Type_error GuessHero(Tree* tree);

Type_error GetLine(Tree* tree, char** string);

Type_error Save(Tree* tree);

void TreeShow(Tree* tree);

void PrintNode(Node* node, size_t* number_of_node, Child child);

void NodeGraph(Node* node, size_t* number_of_node, Child child); 

void GraphEdge(size_t from, size_t to, Child child);

Type_error DescribeHero(Tree* tree);

Type_error DescribeHeroNode(Tree* tree, Node* node, Stack* stk);

bool FindHero(Tree* tree, Node* node, char* hero, Node** dest);

Type_error CompareHeroes(Tree* tree);


