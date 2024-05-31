#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    uint32_t data;
    struct NODE *previous;
    struct NODE *next;
} NODE;

void print_one_node(NODE *someNode)
{
    if (someNode != NULL)
    {
        printf("CURRENT NODE       : %x\n", someNode);
        printf("Pointer to previous: %x\n", someNode->previous);
        printf("Pointer to next:     %x\n", someNode->next);
        printf("Data:                %x\n\n", someNode->data);
    }
    else
    {
        printf("----> Print one node: NULL pointer <----\n");
    }
}

NODE *find_last_node(NODE *head)
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
    return current;
}

void print_all_nodes(NODE *someNode)
{
    uint32_t counter = 0;
    NODE *node = someNode;

    do
    {
        print_one_node(node);
        node = node->next;
        counter++;
    } while (node->next != NULL);
    print_one_node(node);
    printf("Counter: %d \n", counter);
}

void append_node(NODE *someNode)
{
    static uint32_t someData = 0;

    NODE *last = find_last_node(someNode);
    NODE *new = (NODE *)malloc(sizeof(NODE));

    last->next = new;

    new->previous = last;
    new->next = NULL;
    new->data = someData;

    someData++;
}

NODE* get_nth_node_of_list(NODE *firstNode, uint32_t n)
{   
    NODE* auxNode = firstNode;

    for(uint32_t i = 0 ; i < n ; i++)
    {
        if(auxNode->next == NULL)
        {
            return NULL;
        }
        else
        {
            auxNode = auxNode->next;
        }
    }

    return auxNode;
}

NODE* insert_new_node_after(NODE *thisNode)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->data = 0;

    if (thisNode->next != NULL)
    {
        thisNode->next->previous = new;
        new->next = thisNode->next;
        thisNode->next = new;
        new->previous = thisNode;
    }
    else
    {
        thisNode->next = new;
        new->previous = thisNode;
    }

    return new;
}

int main(void)
{
    NODE fistNode = {0};

    fistNode.data = 80;

    for (uint32_t i = 0; i < 10; i++)
    {
        append_node(&fistNode);
    }
    
    print_all_nodes(&fistNode);
    printf("\n\n-----------\n\n");

    insert_new_node_after(insert_new_node_after(get_nth_node_of_list(&fistNode, 3)));
    print_all_nodes(&fistNode);

    return 0;
}
