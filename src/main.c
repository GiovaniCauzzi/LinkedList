#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    uint32_t data;
    struct NODE *previous;
    struct NODE *next;
} NODE;

void print_one_node(NODE * someNode)
{
    printf("CURRENT NODE       : %x\n", someNode);
    printf("Pointer to previous: %x\n", someNode->previous);
    printf("Pointer to next:     %x\n", someNode->next);
    printf("Data:                %x\n\n", someNode->data);
}

NODE* find_last_node(NODE *head)
{
    uint32_t counter = 0;
    if (head == NULL)
        return NULL;

    NODE *current = head;

    while (current->next != NULL)
    {
        counter++;
        current = current->next;
    }


    // printf("Last node iterations: %d \n", counter);
    return  current;
}

void print_all_nodes(NODE * someNode)
{
    uint32_t counter = 0; 
    NODE *node = someNode;
    
    do 
    {
        print_one_node(node);
        node = node->next;
        counter++;
    }while (node->next != NULL) ;
    printf("Counter: %d \n", counter);
}

void append_node(NODE * someNode)
{
    static uint32_t someData = 0;

    NODE *last = find_last_node(someNode);
    NODE *new = (NODE*)malloc(sizeof(NODE));

    last->next = new;

    new->previous = last;
    new->next = NULL;
    new->data = someData;

    someData++;
}


int main(void)
{
    NODE someNode = {0};

    someNode.data = 80;

    for (uint32_t i = 0; i < 25500; i++)
    {
        append_node(&someNode);
    }
    print_all_nodes(&someNode);

    return 0;
}
