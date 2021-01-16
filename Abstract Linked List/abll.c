#include "abll.h"

/*PUSH*/
/*Adds an element to the end of a linked-list*/
/*Returns a pointer (void*) to the beginning of the linked-list*/
void *Abll_push(void* this, void* element)
{
    assert((pLink)element!=NULL);
    if (element==NULL)
    {
        fprintf(stderr, "%s", "ERROR! PUSH - Illegal element\n");
        return this;
    }
    
    int size = Abll_size(this);
    //case list is empty - just shift//
        if (size == 0)
        {
            ((pLink)element)->next = this;
            return element;
        }

    void* last_element = this;
    for (int i = 0; i < size-1; i++)
    {
        last_element=((pLink)last_element)->next;
    }
    ((pLink)last_element)->next = element;
    ((pLink)element)->next = NULL;
    return this;
}
/*POP*/
/*Removes the last element from the linked-list*/
/*Returns a pointer (void*) to the modified linked-list*/
/*sets its 2nd parameter to point to the element removed or NULL if the linked-list was empty*/
void *Abll_pop(void *this, void** element)//NEED TO FIX
{
    assert((pLink)element!=NULL);
    assert((pLink)this!=NULL);
    if (this==NULL){
        fprintf(stderr, "%s", "ERROR! POP - The list is empty\n");
        return this;
    }
    int size = Abll_size(this);
    //case list is empty - just return//
        if (size == 0)
        {
            return this;
        }

    void* last_element = this;
    for (int i = 0; i < size-2; i++)
    {
        last_element=((pLink)last_element)->next;
    }
    *element=((pLink)last_element)->next;
    ((pLink)last_element)->next = NULL;
    return this;
}

/*SHIFT*/
/*Add an element at the beginning of a linked-list*/
/*Returns a pointer (void*) to the new beginning of the linked-list.*/
void *Abll_shift(void *this, void *element)
{
    assert((pLink)element!=NULL);
    if (element==NULL){
        fprintf(stderr, "%s", "ERROR! SHIFT - Illegal element\n");
        return this;
    }
    ((pLink)element)->next = this;
    return element;
}

/*UNSHIFT*/
/*UNSHIFT – Remove the first Element on the linked-list*/
/*Returns a pointer (void*) to the modified linked-list*/
/*sets its 2nd parameter to point to the element removed or NULL if the linked-list was empty*/
void *Abll_unshift(void *this, void **element)
{
    assert((pLink)element!=NULL);
    assert((pLink)this!=NULL);
    if (this==NULL){
        fprintf(stderr, "%s", "ERROR! UNSHIFT - The list is empty\n");
        return this;
    }
    *element=this;
    element=&this;
    this=((pLink)this)->next;
    return this;
}

/*SIZE*/
/*Returns the number of elements in the linked-list*/
int Abll_size(void *this)
{
    assert(&this!=NULL);

    int size = 0;
    void *element = (pLink)this;
    while ((pLink)element != NULL)
    {
        element = ((pLink)element)->next;
        size++;
    }
    return size;
}

/*FILTER*/
/*Removes elements that DO NOT pass the filter from the linked-list*/
void *AbFilter(void *this, BOOL (*FilterElement)(void *, int), int val, void **removed)
{
    assert(&this!=NULL);
    if (this==NULL){
        fprintf(stderr, "%s", "ERROR! FILTER - The list is empty\n");
        return this;
    }
    
    int size = Abll_size(this);
    pLink filtered=NULL;
    *removed=NULL;
    void* p_this=this;
    for (int i = 0; i < size; i++)
    {
        this=Abll_unshift(this,&p_this);
        if ((*FilterElement)(p_this, val)==FALSE)
        {
            *removed=Abll_push(*removed, p_this);
        }
        else
        {
            filtered=Abll_push(filtered, p_this);
        }
    }
    return filtered;
}
