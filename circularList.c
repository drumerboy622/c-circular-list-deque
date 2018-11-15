/*
Author: Matthew Solbrack
Last Updated: 10/29/2018
File: circularList.c
Description: These functions will create a deque
*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	assert(list != 0);
    list -> sentinel = (struct Link*)malloc(sizeof(struct Link));
    assert(list -> sentinel != 0);
    list -> sentinel -> next = list -> sentinel;
    list -> sentinel -> prev = list -> sentinel;
    list -> size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link* newLink = (struct Link*)malloc(sizeof(struct Link));
    assert(newLink != NULL);
    newLink -> value = value;
	return(newLink);
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);
    assert(link != NULL);
    struct Link* newLink = createLink(value);
    assert(newLink != NULL);
    list -> size++;
    link -> next -> prev = newLink;
    newLink -> next = link -> next;
    link -> next = newLink;
    newLink -> prev = link;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
    assert(list != NULL);
    assert(list -> size != 0);
    assert(link != NULL);
    link -> prev -> next = link -> next;
    link -> next -> prev = link -> prev;
    list -> size--;
    free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
    while(list -> size != 0)
    {
        circularListRemoveFront(list);
    }
    free(list -> sentinel);
    list -> sentinel = NULL;
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{

    assert(list != NULL);
    addLinkAfter(list, list -> sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
    assert(list != NULL);
    addLinkAfter(list, list -> sentinel -> prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
    assert(list != NULL);
    assert(list -> size != 0);
	return(list -> sentinel -> next -> value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
    assert(list != NULL);
    assert(list -> size != 0);
	return(list -> sentinel -> prev -> value);
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
    assert(list != NULL);
    assert(list -> size != 0);
    removeLink(list, list -> sentinel -> next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    assert(list != NULL);
    assert(list -> size != 0);
    removeLink(list, list -> sentinel -> prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
    assert(list != NULL);
    if(list -> size == 0)
    	return 1;
    else
        return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
    assert(list != NULL);
    assert(list -> size != 0);
    struct Link* printValue;
    printValue = list -> sentinel -> next;
    while(printValue != list -> sentinel)
    {
        printf("%g ", printValue -> value);
        printValue = printValue -> next;
    }
    printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    assert(list != NULL);
    assert(list -> size != 0);
    struct Link* link;
    struct Link* link2;
    link = list -> sentinel -> next;
    list -> sentinel -> prev = link;
    while(link != list -> sentinel)
    {
         link2 = link -> next;
         if(link2 -> next == list -> sentinel)
             list -> sentinel -> next = link2;
         link -> next = link -> prev;
         link -> prev = link2;
         link = link2;
    }
}
