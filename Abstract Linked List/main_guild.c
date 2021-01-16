#include "Abll.h"
typedef struct _linkable_person
{
    LINK link;
    int id;
    char first[20], last[40];
    struct _date
    {
        int d, m, y;
    } born;
} Person, *PPerson;
int main(void)
{
    Person people[] = {
        {{NULL}, 1111111, "Israel", "Israeli", {5, 5, 1988}},
        {{NULL}, 2222222, "Douglas", "Adams", {1, 11, 1948}},
        {{NULL}, 3333333, "Tuval", "Shem Tov", {15, 7, 1992}},
        {{NULL}, 4444444, "Shimrit", "Cohen", {3, 12, 1980}}};
    PPerson guild = NULL, p; // A guild is an association of craftsmen or merchants (it has a list of members)
    guild = Abll_push(guild, &people[0]);
    guild = Abll_push(guild, &people[1]);
    guild = Abll_shift(guild, &people[2]);
    guild = Abll_shift(guild, &people[3]);
    p = guild;
    printf("The members of the guild are:\n");
    for (int i = 0; i < 4; ++i, p = (PPerson)p->link.next)
        printf("id:%d[%s %s] =>\n", p->id, p->first, p->last);
    printf("(END)\n");
    for (int i = 0; i < 2; ++i)
    {
        guild = Abll_pop(guild, (void **)&p);
        printf("id:%d[%s %s]\n", p->id, p->first, p->last);
        guild = Abll_unshift(guild, (void **)&p);
        printf("id:%d[%s %s]\n", p->id, p->first, p->last);
    }
    if (guild)
        printf("And now guild contains: %p\n", guild);
    else
        printf("And now guild is EMPTY\n");
}