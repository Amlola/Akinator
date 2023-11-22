#include "akinator.h"


void Game(Tree* tree, FILE* data_base, Text* data)
    {
    char c = 0;

    while (c != 'e')
        {
        printf("Choose option: exit_with_[s]ave/[g]uess_hero/[d]escribe/[c]ompare/[t]ree_show/[e]xit_without_save\n");

        c = getc(stdin);
        getc(stdin);

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
                break;
            }
        }
    }


Type_error GuessHero(Tree* tree) 
    {
    Node* node = tree->root;

    char* ans = nullptr;
    
    while (node->left != nullptr && node->right != nullptr)
        {
        printf("Your hero is %s?(yes/no)\n", node->data);

        GetLine(tree, &ans);

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

    GetLine(tree, &ans);

    if (strcmp(ans, "yes") == 0)
        {
        printf("I know. It's easy\n");
        }

    else
        {
        printf("Okey, then tell me\n");

        printf("Who was that?\n");

        char* node_right_string = nullptr;

        GetLine(tree, &node_right_string);

        printf("And how are %s different from %s?\n", node_right_string, node->data);

        char* characteristic = nullptr;

        GetLine(tree, &characteristic);

        const char* node_left_string = node->data;

        node->data = characteristic;

        TreeInsert(tree, node, node_left_string, L_CHILD);

        TreeInsert(tree, node, node_right_string, R_CHILD);
        }

    return tree->status;
    }



Type_error GetLine(Tree* tree, char** string)
    {
    *string = (char*)calloc(MAX_STRING_LEN, sizeof(char));

    char c =  0;

    size_t ptr  =  0;

    while (true)
        {
        c = getchar();

        if (c == '\n')
            {
            (*string)[ptr] = '\0';

            return tree->status;
            }

        (*string)[ptr++] = c;
        }

    return tree->status;
    }



Type_error Save(Tree* tree) 
    {
    FILE* data_base = fopen("tree.txt", "w");

    TreePrefixPrint(tree, tree->root, data_base);

    fclose(data_base);
    }



void NodeGraph(Node* node, size_t* number_of_node, Child child) 
    {
    PrintNode(node, number_of_node, child);

    size_t current_number_of_node = *number_of_node;

    if (node->left)
        {
        GraphEdge(current_number_of_node, ++(*number_of_node), L_CHILD);

        NodeGraph(node->left, number_of_node, L_CHILD);
        }

    if (node->right)
        {
        GraphEdge(current_number_of_node, ++(*number_of_node), R_CHILD);

        NodeGraph(node->right, number_of_node, R_CHILD);
        } 
    }


void GraphEdge(size_t from, size_t to, Child child) 
    {
    if (child == L_CHILD)
        {
        print("node%d->node%d [color = \"lime\"];\n", from, to);
        }

    else
        {
        print("node%d->node%d [color = \"aqua\"];\n", from, to);
        }
    }


void PrintNode(Node* node, size_t* number_of_node, Child child) 
    {
    if (*number_of_node == 0) 
        {
        print("node%d[shape=record, style=filled, fillcolor=\"red\", label=\" {%s}\"];\n", 
                                              *number_of_node, node->data);
        }

    else 
        {
        if (child == L_CHILD) 
            {
            print("node%d[shape=record, style=filled, fillcolor=\"lime\", label=\" {%s}\"];\n", 
                                              *number_of_node, node->data);
            }
        else 
            {
            print("node%d[shape=record, style=filled, fillcolor=\"aqua\", label=\" {%s}\"];\n", 
                                              *number_of_node, node->data);  
            }
        }
    }


void TreeShow(Tree* tree) 
    {
    size_t number_of_node = 0;

    graph_file = fopen("dotfile.dot", "wb");

    print("digraph struct {bgcolor=RosyBrown rankdir = HR\n\n\n");

    NodeGraph(tree->root, &number_of_node, L_CHILD);

    print("\n\n}");

    fclose(graph_file);

    char shell_command[MAX_COMMAND_LENGTH] = "";
        sprintf(shell_command, "dot -v -Tpng D:/Cprojects/Akinator/dotfile.dot -o D:/Cprojects/Akinator/graph.png");
        system(shell_command);
    }



bool FindHero(Tree* tree, Node* node, char* hero, Node** dest)
    {
    if (*dest != nullptr) return true;

    bool find = false;
     
    if (strcmp(node->data, hero) == 0)
        {
        *dest = node;

        return true;
        }

    else
        {
        if (node->left)  
            {
            find = FindHero(tree, node->left, hero, dest);
            }

        if (node->right) 
            {
            find = FindHero(tree, node->right, hero, dest); 
            }

        if (find) 
            {
            return find;
            }
        }
    
    return find;
    }


Type_error DescribeHeroNode(Tree* tree, Node* node, Stack* stk)
    {
    if (node == nullptr) 
        {
        return NODE_PTR_IS_NULL;
        }

    CHECKERROR(stk);

    while (node->parent != nullptr)
        {
        StackPush(stk, (char*)node);

        node = node->parent;
        }
        
    return tree->status;
    }


Type_error DescribeHero(Tree* tree) 
    {
    printf("Which hero would you like to describe?\n");

    char* hero = nullptr;

    GetLine(tree, &hero);

    Node* node = nullptr;

    Stack stk = {};

    StackCtor(&stk);

    if (FindHero(tree, tree->root, hero, &node) == true)
        {
        DescribeHeroNode(tree, node, &stk);

        printf("%s? I find! He is ", node->data);

        Node** nodes = (Node**)stk.stack_data;

        Node* tmp_node  = nullptr;

        size_t it = stk.stack_pos - 1;

        do 
            {
            tmp_node = nodes[it];

            if (tmp_node->left == nodes[it - 1])
                {
                printf("not ");
                }

            printf("%s/ ", tmp_node->data);
            
            it--;
            }

        while (it > 0 && it != (size_t)(-1));

        printf("\n");
    
        }
    else
        {
        printf("I don't find this hero!\n");
        }

    StackDtor(&stk);

    return tree->status;
    }



Type_error CompareHeroes(Tree* tree) 
    {
    printf("Who do you want to compare?\n");

    char* hero[2] = {};

    for (size_t i = 0; i < 2; i++) 
        {
        printf("Hero number %d: ", i + 1);

        GetLine(tree, &hero[i]);
        }  


    Stack stks[2]  = {};

    Node* nodes[2] = {};

    bool find = true;

    for (size_t i = 0; i < 2; i++)
        {
        StackCtor(&stks[i]);

        if (FindHero(tree, tree->root, hero[i], &nodes[i]) == false) 
            {
            find = false;

            break;
            }
        }
    
    if (find) 
        {
        for (size_t i = 0; i < 2; i++)
            {
            DescribeHeroNode(tree, nodes[i], &stks[i]);
            }

        Node** Nodes[2]   = {};

        Node* tmp_node[2] = {};

        size_t it[2]      = {};

        for (size_t i = 0; i < 2; i++)
            {
            Nodes[i]    = (Node**)stks[i].stack_data;

            it[i]       = stks[i].stack_pos - 1;

            tmp_node[i] = Nodes[i][it[i]];
            }

        int flag = 0;

        while (tmp_node[0] == tmp_node[1] && tmp_node[0]->left == Nodes[0][it[0] - 1])
            { 
            if (flag == 0) 
                {  
                printf("%s and %s similar in that they ", nodes[0]->data, nodes[1]->data);
                }

            if (tmp_node[0]->left == Nodes[0][it[0] - 1])
                {
                printf("not ");
                }
            
            printf("%s/ ", tmp_node[0]->data);

            for (size_t i = 0; i < 2; i++)
                {
                it[i] = it[i] - 1;

                tmp_node[i] = Nodes[i][it[i]];
                }

            flag++;
            }  

        if (flag == 0) 
            {
            printf("%s and %s same\n", nodes[0]->data, nodes[1]->data); 
            }
        
        else 
            {
            for (size_t i = 0; i < 2; i++)
                {
                if (i == 0)
                    {
                    printf("but %s ", nodes[i]->data);
                    }

                else
                    {
                    printf("and %s ",  nodes[i]->data);
                    }

                do  
                    {
                    tmp_node[i] = Nodes[i][it[i]];

                    if (tmp_node[i]->left == Nodes[i][it[i] - 1])
                        {
                        printf("not ");
                        }

                    printf("%s/ ", tmp_node[i]->data);
                    
                    it[i]--;
                    }
                
                while (it[i] > 0);

                printf("\n");
                }
            }

        for (size_t i = 0; i < 2; ++i)
            {
            StackDtor(&stks[i]);
            }    
        }
    }
