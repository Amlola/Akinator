#include "TXLib.h"
#include "tree.h"
#include "stack.h"





const size_t MAX_STRING_LEN = 100;


const size_t MAX_ANS_LEN = 10;


void Game(Tree* tree);

Type_error GuessHero(Tree* tree);

Type_error GetLine(Tree* tree, char string[], size_t MAX_INPUT_LEN);

Type_error Save(Tree* tree);

void TreeShow(Tree* tree);

void PrintNode(Node* node, size_t* number_of_node, Child child, const char* color); 

void NodeGraph(Node* node, size_t* number_of_node, Child child, const char* color); 

void GraphEdge(size_t from, size_t to, Child child, const char* color); 

Node* GetNode(Node* node, char* name);

Type_error DescribeHero(Tree* tree);

Type_error FindPath(Tree* tree, Node* node, Stack* stk);

void TellAbout(Node* node, Stack* stk);

void TellAbout(Node* node, Stack* stk);

Type_error CompareHeroes(Tree* tree);

Type_error GetDifferent(Tree* tree, Node* node);