// list/list.c
//
// Implementation for linked list.
//
// <Sariah Adams>

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t *list_alloc() {
    list_t *mylist = (list_t *)malloc(
        sizeof(list_t));  // malloc and sizeof are built-in functions
    mylist->head = NULL;
    return mylist;
}

void list_free(list_t *l) {
    // check if the list exists; if not, there's no memory to give back!
    if (l == NULL) return;  // breaks us out of the function

    // remove each node from the list
    while (l->head != NULL) list_remove_from_front(l);

    free(l);  // built in C function that returns memory
}

void list_print(list_t *l) {
    // check if the list exists; if not, there's nothing to print!
    if (l == NULL) return;

    // check if the list is empty; if not, there's nothing to print!
    if (l->head == NULL) return;

    printf("The List:\n");

    // declare cur_node and set it equal to the head of the list
    node_t *cur_node = (node_t *)malloc(sizeof(node_t));
    cur_node = l->head;

    // traverse list and print node values
    while (cur_node != NULL) {
        printf("%d->", cur_node->value);
        cur_node = cur_node->next;
    }
    printf("NULL\n");
}

char *listToString(list_t *l) {
    char *buf = (char *)malloc(sizeof(char) * 10024);
    char tbuf[20];

    node_t *curr = l->head;
    while (curr != NULL) {
        sprintf(tbuf, "%d->", curr->value);
        curr = curr->next;
        strcat(buf, tbuf);
    }
    strcat(buf, "NULL");
    return buf;
}

int list_length(list_t *l) {
    // check if the list exists
    if (l == NULL) return -1;

    // check if list is empty; if it is, there's nothing in the list
    if (l->head == NULL) return 0;

    // declare cur_node and set it equal to the head of the list
    node_t *cur_node = (node_t *)malloc(sizeof(node_t));
    cur_node = l->head;

    // declare node_count to track how many nodes in the list
    int node_count = 0;

    // traverse list and increment counter
    while (cur_node != NULL) {
        node_count++;               // increment the count
        cur_node = cur_node->next;  // go to next node in list
    }

    return node_count;
}

void list_add_to_back(list_t *l, elem value) {
    // checks if the list exists
    if (l == NULL) return;

    // create a new node
    node_t *new_node =
        (node_t *)malloc(sizeof(node_t));  // making space in memory
    new_node->value = value;               // set its value
    new_node->next = NULL;                 // set its next pointer

    // check if the list is empty; if it is, then the "back" of the list is the
    // same as the head
    if (l->head == NULL) {
        l->head = new_node;
        return;
    }

    // if the list is not empty, traverse to the end and add the new node there
    node_t *tmp = l->head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = new_node;
}

void list_add_to_front(list_t *l, elem value) {
    // checks if the list exists
    if (l == NULL) return;

    // create a new node
    node_t *new_node =
        (node_t *)malloc(sizeof(node_t));  // making space in memory
    new_node->value = value;               // set its value
    new_node->next = NULL;                 // set its next pointer

    // check if the list is empty; if it is, then the "front" of the list is the
    // same as the head
    if (l->head == NULL) {
        l->head = new_node;
        return;
    }

    // if there already is a head, we need to set the new node equal to it
    new_node->next = l->head;
    l->head = new_node;
}

node_t *getNode(elem value) {
    node_t *mynode;

    mynode = (node_t *)malloc(sizeof(node_t));
    mynode->value = value;
    mynode->next = NULL;

    return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
    // checks if the list exists
    if (l == NULL) return;

    // check if the list is empty; if it is, create a new head
    if (l->head == NULL) return list_add_to_front(l, value);

    // if index is out of range, don't add it
    if (index < 1 || index > list_length(l) + 2) return;

    // if index == 1 (aka the first index in the list), add to the front
    if (index == 1) return list_add_to_front(l, value);

    // if index == length+1 of the list (aka the last index in the list), add to
    // the back
    if (index == list_length(l) + 1) return list_add_to_back(l, value);

    // if the index is within the range, create node and add it
    // create a new node
    node_t *new_node =
        (node_t *)malloc(sizeof(node_t));  // making space in memory
    new_node->value = value;               // set its value
    new_node->next = NULL;                 // set its next pointer

    int i;                       // keep track of loop iteration
    node_t *cur_node = l->head;  // node to traverse through the list
    for (i = 1; i < index - 1; i++) {
        cur_node = cur_node->next;
    }

    // make the necessary pointer adjustments
    new_node->next = cur_node->next;
    cur_node->next = new_node;
}

elem list_remove_from_back(list_t *l) {
    // check if list exists
    if (l == NULL) return -1;

    // check if head exists; if it doesn't there is nothing to remove
    if (l->head == NULL) return -1;

    // if head exists, traverse to 2nd to last node in the list
    node_t *cur_node = (node_t *)malloc(sizeof(node_t));
    cur_node = l->head;

    while (cur_node->next && cur_node->next->next) {
        cur_node = cur_node->next;
    }

    int popped_val;  // value of node that is removed

    // if node is the head, make head point to NULL
    if (cur_node == l->head) {
        popped_val = l->head->value;
        l->head = NULL;
        return popped_val;
    }

    // if node is not the head, make the node point to NULL
    node_t *tmp = cur_node->next;
    free(tmp);  // give memory back
    popped_val = cur_node->next->value;
    cur_node->next = NULL;

    return popped_val;
}

elem list_remove_from_front(list_t *l) {
    // check if list exists
    if (l == NULL) return -1;

    // check if list is empty; if it is, there's nothing to remove
    if (l->head == NULL) return -1;

    // if it isn't, make head point to next node (if it exists)
    int popped_val = l->head->value;
    node_t *tmp = l->head->next;
    free(l->head); // give memory back
    l->head = tmp;

    return popped_val;
}

elem list_remove_at_index(list_t *l, int index) {
    // check if list exists
    if (l == NULL) return -1;

    // check if list is empty; if it is, there's nothing to remove
    if (l->head == NULL) return -1;

    // check if index is out of range
    if (index < 1 || index > list_length(l)) {
        printf("%i is out of range!\n", index);
        return -1;
    }

    // check if index is 1; if it is, remove the old head and leave function
    if (index == 1) return list_remove_from_front(l);

    // iterate to proper node index
    node_t *cur_node = l->head;
    int i;
    for (i = 1; i < index - 1; i++) {
        cur_node = cur_node->next;
    }

    // if possible, delete the node
    if (cur_node != NULL) {
        node_t *tmp = cur_node->next;
        int popped_val = tmp->value;
        cur_node->next = tmp->next;
        free(tmp);
        return popped_val;
    }

    // if not possible, return
    printf("Something went wrong!\n");
    return -1;
}

bool list_is_in(list_t *l, elem value) {
    // check if list exists
    if (l == NULL) return false;

    // check if list is empty; if it is, nothing can be in the list
    if (l->head == NULL) return false;

    // iterate through list and check for presence
    node_t *cur_node = l->head;
    while (cur_node) {
        if (cur_node->value == value) return true;
        cur_node = cur_node->next;
    }
    return false;
}

elem list_get_elem_at(list_t *l, int index) {
    // check if list exists
    if (l == NULL) return -1;

    // check if list is empty; if it is, nothing to get from the list
    if (l->head == NULL) return -1;

    // check if index is out of range
    if (index < 1 || index > list_length(l)) return -1;

    // if the index is valid, iterate to index
    node_t *cur_node = l->head;
    int i;
    for (i = 1; i < index; i++) {
        cur_node = cur_node->next;
    }
    return cur_node->value;
}

int list_get_index_of(list_t *l, elem value) {
    // check if list exists
    if (l == NULL) return -1;

    // check if list is empty; if it is, nothing to get from the list
    if (l->head == NULL) return -1;

    // iterate to value
    node_t *cur_node = l->head;
    int index = 1;
    while (cur_node && cur_node->value != value) {
        index++;
        cur_node = cur_node->next;
    }

    // if possible, return index
    if (cur_node) return index;

    return -1;
}
