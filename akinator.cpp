#include "akinator.h"



void Game(Tree* tree)
    {    
    char c = 0;

    while (c != 'e')
        {
        printf("Choose option: exit_with_[s]ave/[g]uess_hero/[d]escribe/[c]ompare/[t]ree_show/[e]xit_without_save\n");

        char ans[MAX_ANS_LEN] = "";

        GetLine(tree, ans, MAX_ANS_LEN);

        c = ans[0]; 

        if (strlen(ans) > 1) 
            {
            printf("I don't understand\n");

            printf("Try again\n");
            }

        else 
            {
            switch (c)
                {
                case 's':
                    Save(tree);
                    c = 'e';
                    printf("Bye!");
                    break;

                case 't':
                    TreeShow(tree);
                    break;

                case 'e':
                    printf("Bye!");
                    break;

                case 'd':
                    DescribeHero(tree);
                    break;

                case 'c':
                    CompareHeroes(tree);
                    break;

                case 'g':
                    GuessHero(tree);
                    break;

                default:
                    printf("I don't understand\n");
                    printf("Try again\n");
                    break;
                }
            }
        }
    
    TreeDtor(tree);
    }



Type_error GuessHero(Tree* tree) 
    {
    Node* node = tree->root;

    char ans[MAX_ANS_LEN] = "";
    
    while (node->left != nullptr && node->right != nullptr)
        {
        printf("Your hero is %s?(yes/no)\n", node->data);

        GetLine(tree, ans, MAX_ANS_LEN);

        if (strcmp(ans, "yes") == 0)
            {
            node = node->right;
            }

        else if (strcmp(ans, "no") == 0)
            {
            node = node->left;
            }

        else
            {
            printf("I don't understand you. Try again\n");
            }

        }

    printf("It is %s?(yes/no)\n", node->data);

    GetLine(tree, ans, MAX_ANS_LEN);

    if (strcmp(ans, "yes") == 0)
        {
        printf("I know. It's easy\n");
        }

    else if (strcmp(ans, "no") == 0)
        {
        GetDifferent(tree, node);
        }
    
    else 
        {
        printf("I don't understand you. Try again\n");
        }

    return tree->status;
    }



Type_error GetDifferent(Tree* tree, Node* node) 
    {
    printf("Okey, then tell me\n");

    printf("Who was that?\n");

    char* node_right_string = (char*)calloc(MAX_STRING_LEN, sizeof(char));

    GetLine(tree, node_right_string, MAX_STRING_LEN);

    printf("And how are %s different from %s?\n", node_right_string, node->data);

    char* characteristic = (char*)calloc(MAX_STRING_LEN, sizeof(char));

    GetLine(tree, characteristic, MAX_STRING_LEN);

    char* node_left_string = node->data;

    node->data = characteristic;

    TreeInsert(tree, node, node_left_string, L_CHILD);

    TreeInsert(tree, node, node_right_string, R_CHILD);

    return tree->status;
    }



Type_error GetLine(Tree* tree, char string[], size_t MAX_INPUT_LEN)
    {
    char c = 0;

    size_t ptr = 0;

    while (ptr < MAX_INPUT_LEN)
        {
        c = getchar();

        if (c == '\n')
            {
            string[ptr] = '\0';

            return tree->status;
            }

        string[ptr++] = c;
        }

    fflush(stdin);

    printf("Maximum allowed string length is %d.\n", MAX_INPUT_LEN);

    printf("Do you want to save string %s?(yes/no)\n", string);

    char ans[MAX_ANS_LEN] = "";

    scanf("%s", &ans);

    fflush(stdin);

    if (strcmp(ans, "yes") == 0) 
        {
        return tree->status;
        }

    else 
        {
        Game(tree);
        }

    return tree->status;
    }



Type_error Save(Tree* tree) 
    {
    FILE* data_base = fopen("tree.txt", "w");

    TreePrefixPrint(tree, tree->root, data_base);

    fclose(data_base);
    }



void NodeGraph(Node* node, size_t* number_of_node, Child child, const char* color) 
    {
    PrintNode(node, number_of_node, child, color);

    size_t current_number_of_node = *number_of_node;

    if (node->left)
        {
        GraphEdge(current_number_of_node, ++(*number_of_node), L_CHILD, "lime");

        NodeGraph(node->left, number_of_node, L_CHILD, "lime");
        }

    if (node->right)
        {
        GraphEdge(current_number_of_node, ++(*number_of_node), R_CHILD, "aqua");

        NodeGraph(node->right, number_of_node, R_CHILD, "aqua");
        } 
    }


void GraphEdge(size_t from, size_t to, Child child, const char* color) 
    {
    print("node%d->node%d [color = \"%s\"];\n", from, to, color);
    }


void PrintNode(Node* node, size_t* number_of_node, Child child, const char* color) 
    {
    print("node%d[shape=record, style=filled, fillcolor=\"%s\", label=\" {%s}\"];\n", 
                                              *number_of_node, color, node->data);
    }


void TreeShow(Tree* tree) 
    {
    size_t number_of_node = 0;

    graph_file = fopen("dotfile.dot", "wb");

    print("digraph struct {bgcolor=RosyBrown rankdir = HR\n\n\n");

    NodeGraph(tree->root, &number_of_node, L_CHILD, "red");

    print("\n\n}");

    fclose(graph_file);

    char shell_command[MAX_COMMAND_LENGTH] = "";
        sprintf(shell_command, "dot -Tpng dotfile.dot -o graph.png");
        system(shell_command);
        system(".\\graph.png");
    }



Node* GetNode(Node* node, char* name)
    {
    assert (name);

    if (!node)
        {
        return nullptr;
        }

    if (strcmp(node->data, name) == 0)
        {
        return node;
        }

    Node* object = GetNode(node->left, name);

    if (object)
        { 
        return object;
        }

    object = GetNode(node->right, name);

    if (object)
        { 
        return object;
        }

    return nullptr;
    }

    

Type_error DescribeHero(Tree* tree)
    {
    printf("Which hero would you like to describe?\n");

    char hero[MAX_STRING_LEN] = "";

    GetLine(tree, hero, MAX_STRING_LEN);

    Node* object = GetNode(tree->root, hero);

    if (!object)
        {
        printf("I don't find this hero! Try again\n");

        return tree->status;
        }

    Stack stk = {};

    StackCtor (&stk);

    FindPath (tree, object, &stk);

    TellAbout (tree->root, &stk);
    
    putchar('\n');

    StackDtor(&stk);

    return tree->status;
    }



Type_error FindPath(Tree* tree, Node* node, Stack* stk)
    {
    if (node == nullptr) 
        {
        return tree->status;
        }

    while (node->parent != tree->root)
        {
        if (node == node->parent->left)
            {
            StackPush(stk, L_CHILD);

            node = node->parent;
            }

        else
            {
            StackPush(stk, R_CHILD);

            node = node->parent;
            }
        }

    if (tree->root->left == node) 
        {
        StackPush(stk, L_CHILD);
        }

    if (tree->root->right == node) 
        {
        StackPush(stk, R_CHILD);
        }

    return tree->status;
    }

    

void TellAbout(Node* node, Stack* stk)
    {
    Child way = L_CHILD;

    StackPop(stk, (int*)&way);

    if (way == L_CHILD)
        {
        printf("not %s", node->data);

        node = node->left;
        }

    else
        {
        printf("%s", node->data);

        node = node->right;
        }

    if (node->left && node->right)
        {
        printf (", ");

        TellAbout (node, stk);
        }
    }



Type_error CompareHeroes(Tree* tree) 
    {
    printf("Who do you want to compare?\n");

    char* hero[2] = {};

    for (size_t i = 0; i < 2; i++) 
        {
        printf("Hero number %d: ", i + 1);

        hero[i] = (char*)calloc(MAX_STRING_LEN, sizeof(char));

        GetLine(tree, hero[i], MAX_STRING_LEN);
        } 

    Stack stks[2]  = {};

    Node* nodes[2] = {};

    int count_again = 0;

    for (size_t i = 0; i < 2; i++)
        {
        nodes[i] = GetNode(tree->root, hero[i]);

        if (nodes[i] == nullptr) 
            {
            printf("I don't find the %d hero!\n", i + 1);

            printf("Try again\n");

            return tree->status;
            }

        StackCtor(&stks[i]);

        FindPath(tree, nodes[i], &stks[i]);
        }

    Child way1 = L_CHILD;

    Child way2 = L_CHILD;

    StackPop(&stks[0], (int*)&way1);

    StackPop(&stks[1], (int*)&way2);

    int flag = 0;

    Node* tmp_node = tree->root;

    while (way1 == way2) 
        {
        if (flag == 0) 
            {
            printf("%s and %s similar in that they ", nodes[0]->data, nodes[1]->data);
            }
        
        if (way1 == L_CHILD)
            {
            printf("not %s, ", tmp_node->data);

            tmp_node = tmp_node->left;
            }
        
        else 
            {
            printf("%s, ", tmp_node->data);

            tmp_node = tmp_node->right;
            }

        if (stks[0].stack_pos == 0 && stks[1].stack_pos == 0) 
            {
            printf("They are same\n");
            
            return tree->status;
            } 

        StackPop(&stks[0], (int*)&way1);

        StackPop(&stks[1], (int*)&way2);

        flag++;
        }

      
    StackPush(&stks[0], way1);

    StackPush(&stks[1], way2);

    if (flag == 0) 
        {
        printf("They are nothing alike, but %s ", nodes[0]->data);
        }

    else 
        {
        printf("but %s ", nodes[0]->data);
        }


    TellAbout(tmp_node, &stks[0]);

    printf(", and %s ", nodes[1]->data);

    TellAbout(tmp_node, &stks[1]);
    
    putchar('\n');
    }
