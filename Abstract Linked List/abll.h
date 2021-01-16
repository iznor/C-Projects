#ifndef ABLL_H
#define ABLL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _link
{
    struct _link *next;
} LINK, *pLink;

typedef enum _bool
{
    FALSE,
    TRUE
} BOOL;

void *Abll_push(void *this, void *element);
void *Abll_pop(void *this, void **element);
void *Abll_shift(void *this, void *element);
void *Abll_unshift(void *this, void **element);
int Abll_size(void *this);
void *AbFilter(void *this, BOOL (*FilterElement)(void *, int), int val, void **removed);

#endif
