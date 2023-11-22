#include "akinator.h"



int main() 
    {
    Tree tree = {};

    TreeCtor(&tree);

    Text data = {};

    FILE* data_base = fopen("tree.txt", "r");

    FileInput(data_base, &data);

    TreeRead(&tree, &data);

    fclose(data_base);

    Game(&tree, data_base, &data);

    return 0;
    }