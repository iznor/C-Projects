#include "Abll.h"
BOOL filterCourses(void *ele, int val);
BOOL filterGrade(void *ele, int val);
typedef struct _linkable_student
{
    LINK link;
    int student_id;
    char first[10], last[12];
    int numberOfCourses;
    double average;
} Student, *PStudent;
void displayList(PStudent studentL)
{
    if (!studentL)
        printf(" <<Empty>>\n");
    for (; studentL; studentL = (PStudent)studentL->link.next)
        printf("%d %-10s %-12s has %d courses Avg:%g\n",
               studentL->student_id, studentL->first, studentL->last,
               studentL->numberOfCourses, studentL->average);
    printf("\n");
}
int main(void)
{
    Student shenkar[] = {
        {{NULL}, 1111111, "Amos", "Levi", 12, 82.8},
        {{NULL}, 2222222, "Tanchum", "Haroea", 4, 92.5},
        {{NULL}, 3333333, "Gali", "Shabat", 20, 62.9},
        {{NULL}, 4444444, "Hanoch", "Cohen", 18, 73.3},
        {{NULL}, 5555555, "Tali", "Bahat", 6, 72.2},
        {{NULL}, 6666666, "Sharon", "Shalev", 14, 81.4}};
    PStudent Tashaf = NULL;
    for (int i = 0; i < sizeof(shenkar) / sizeof(Student); ++i)
        Tashaf = Abll_shift(Tashaf, &shenkar[i]);
    printf("Original List:\n");
    displayList(Tashaf);
    PStudent filtered, removed;
    filtered = AbFilter(Tashaf, filterCourses, 10, (void **)&removed);
    printf("\nAfter filtering for courses>10:\n");
    displayList(filtered);
    printf("Removed:\n");
    displayList(removed);
    filtered = AbFilter(filtered, filterGrade, 80, (void **)&removed);
    printf("\nAfter filtering the above for grade Average > 80:\n");
    displayList(filtered);
    printf("Removed:\n");
    displayList(removed);
}
BOOL filterCourses(void *ele, int val)
{
    PStudent student = (PStudent)ele;
    return student->numberOfCourses > val;
}
BOOL filterGrade(void *ele, int val)
{
    PStudent student = (PStudent)ele;
    return student->average > (double)val;
}
