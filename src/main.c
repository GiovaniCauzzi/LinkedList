#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

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
        printf("CURRENT NODE       : 0x%x\n",   someNode);
        printf("Pointer to previous: 0x%x\n",   someNode->previous);
        printf("Pointer to next:     0x%x\n",   someNode->next);
        printf("Data:                0x%x\n\n", someNode->data);
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

NODE *find_first_node(NODE *head)
{
    uint32_t counter = 0;
    if (head == NULL)
        return NULL;

    NODE *current = head;

    while (current->previous != NULL)
    {
        counter++;
        current = current->previous;
    }

    // printf("First node iterations: %d \n", counter);
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

NODE *get_nth_node_from_current(NODE *someNode, int32_t n)
{
    NODE *auxNode = someNode;

    if (n >= 0)
    {
        for (uint32_t i = 0; i < n; i++)
        {
            if (auxNode->next == NULL)
            {
                return NULL;
            }
            else
            {
                auxNode = auxNode->next;
            }
        }
    }
    else
    {
        for (int32_t i = 0; i > n; i--)
        {
            if (auxNode->previous == NULL)
            {
                return NULL;
            }
            else
            {
                auxNode = auxNode->previous;
            }
        }
    }

    return auxNode;
}

NODE *get_nth_node_of_list(NODE *someNode, uint32_t n)
{
    NODE *auxNode = find_first_node(someNode);
    // find the first and then get the nth node of the list
    for (uint32_t i = 0; i < n; i++)
    {
        if (auxNode->next == NULL)
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

NODE *insert_new_node_after(NODE *thisNode)
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

uint8_t exclude_node(NODE *someNode)
{
    if (someNode == NULL)
    {
        return FALSE;
    }

    if (someNode->previous != NULL && someNode->next != NULL)
    {
        someNode->next->previous = someNode->previous;
        someNode->previous->next = someNode->next;
    }
    else if (someNode->previous != NULL)
    {
        someNode->previous->next = NULL;
    }
    else if (someNode->next != NULL)
    {
        someNode->next->previous = NULL;
    }
    free(someNode);
    return TRUE;
}

int main(void)
{
    // TEST_insert_node_process();
    // TEST_find_first_or_last_node_process();
    // TEST_get_nth_node_process();
    TEST_exclude_node_process();
    return 0;
}

void TEST_insert_node_process()
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
}

void TEST_find_first_or_last_node_process()
{
    NODE fistNode = {0};
    fistNode.data = 80;

    for (uint32_t i = 0; i < 10; i++)
    {
        append_node(&fistNode);
    }
    // print_one_node((get_nth_node_of_list(&fistNode, 3)));
    print_one_node(find_first_node(get_nth_node_of_list(&fistNode, 3)));
    print_one_node(find_last_node(get_nth_node_of_list(&fistNode, 3)));
    printf("\n\n-----------\n\n");
    print_all_nodes(&fistNode);
}

void TEST_get_nth_node_process()
{
    NODE fistNode = {0};

    fistNode.data = 80;

    for (uint32_t i = 0; i < 10; i++)
    {
        append_node(&fistNode);
    }
    print_all_nodes(&fistNode);
    printf("\n\n-----------\n\n");

    printf("-------------------- 5th node: --------------------\n");
    print_one_node(get_nth_node_of_list(&fistNode, 5));
    printf("-------------------- 7th node: --------------------\n");
    print_one_node(get_nth_node_from_current(get_nth_node_of_list(&fistNode, 5), 2));
    printf("-------------------- 3rd node: --------------------\n");
    print_one_node(get_nth_node_from_current(get_nth_node_of_list(&fistNode, 5), -2));
}

void TEST_exclude_node_process()
{
    uint32_t qtyOfNodes = 10;
    NODE fistNode = {0};
    fistNode.data = 80;

    for (uint32_t i = 0; i < qtyOfNodes; i++)
    {
        append_node(&fistNode);
    }
    print_all_nodes(&fistNode);
    printf("\n\n-----------\n\n");
    // exclude_node(get_nth_node_of_list(&fistNode, 0));
    // exclude_node(get_nth_node_of_list(&fistNode, 5));
    if (exclude_node(get_nth_node_of_list(&fistNode, 1)))
    {
        print_all_nodes(&fistNode);
    }
    else
    {
        printf("Fail \n");
    }
}