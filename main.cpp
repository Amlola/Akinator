#include "akinator.h"



int main() 
    {
    Tree tree = {};

    TreeCtor(&tree);

    Text data = {};

    FILE* data_base = fopen("tree.txt", "r");

    FileInput(data_base, &data);

    TreeRead(&tree, &data);

    txPlaySound(".\\music1.wav");

    Game(&tree);

    return 0;
    }