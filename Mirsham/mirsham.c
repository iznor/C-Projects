#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct PERSON
{
    char fullname[40];
    char id[40];
    char st_apt[40];
    char city[50];
} citizen;

int Arg_Check(int argc, int n);                        //prints "error" & returns 0 if argc < n
int fp_Check(FILE *fp);                                //prints "error" & returns 0 if fp==NULL
int does_exist(const char *filename, const char ID[]); //returns 1 if citizen exists
void add_obj(const char *filename, citizen *p);        //adds citizen
void print_all(FILE *fp);                              //prints full report
void find(const char *filename, const char ID[]);      //prints details of pecific citizen if his ID found

int main(int argc, char const *argv[])
{
    citizen person, *p = &person;
    FILE *fp;
    if (strcmp(argv[1], "add") == 0) //case add//
    {
        if (Arg_Check(argc, 2))
        {
            add_obj(argv[2], p);
        }
        return 0;
    }
    if (strcmp(argv[1], "print") == 0) //case print//
    {
        if (Arg_Check(argc, 2))
        {
            fp = fopen(argv[2], "r");
            if (fp_Check(fp))
            {
                print_all(fp);
            }
        }
        return 0;
    }
    if (strcmp(argv[1], "find") == 0) //case find//
    {
        if (Arg_Check(argc, 3))
        {
            find(argv[3], argv[2]);
        }
        return 0;
    }
    fclose(fp); //just to make sure.
    return 0;
}

int Arg_Check(int argc, int n) //prints "error" if argc < n
{
    if (argc < n)
    {
        printf("Error!");
        return 0;
    }
}

int fp_Check(FILE *fp) //prints "error" if fp==NULL
{
    if (fp == NULL)
    {
        printf("Error!");
        return 0;
    }
}

int does_exist(const char *filename, const char ID[]) //returns 1 if citizen exists already
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error!");
        return 0;
    }

    int ex = 0;
    char buf[100];
    while (fgets(buf, 100, fp) != NULL)
    {
        if (buf[0] == '#' || buf[0] == '\n')
        {
            continue;
        }
        if (buf[0] == '-')
        {
            char details[100] = {0};
            char id[10] = {0};
            for (int i = 1; i <= 4; i++)
            {
                fgets(details, 100, fp);
                details[strlen(details) - 1] = ' ';
                if (i == 2)
                {
                    strcpy(id, details);
                    id[strlen(id) - 1] = '\0';
                }
                if (strcmp(ID, id) == 0)
                {
                    ex = 1;
                }
            }
        }
    }
    fclose(fp);
    return ex;
}

void add_obj(const char *filename, citizen *p) //add citizen
{
    FILE *fp;
    fp = fopen(filename, "a");
    if (fp_Check(fp))
    {
        gets(p->fullname);
        gets(p->id);
        gets(p->st_apt);
        gets(p->city);
        if (does_exist(filename, p->id) == 1)
        {
            printf("Error! Citizen already exists\n");
            return;
        }
        fprintf(fp, "\n");
        fprintf(fp, "%s\n", p->fullname, fp);
        fprintf(fp, "%s\n", p->id, fp);
        fprintf(fp, "%s\n", p->st_apt, fp);
        fprintf(fp, "%s\n", p->city, fp);
        fprintf(fp, "-");
        fclose(fp);
    }
}

void print_all(FILE *fp) //print full report
{
    char buf[100];
    while (fgets(buf, 100, fp) != NULL)
    {
        if (buf[0] == '#' || buf[0] == '\n')
        {
            continue;
        }
        if (buf[0] == '-')
        {
            char details[100] = {0};
            char person[100] = {0};
            for (int i = 1; i <= 4; i++)
            {
                fgets(details, 100, fp);
                details[strlen(details) - 1] = ' ';
                strcat(person, details);
            }
            printf("%s", person);
            if (person[strlen(person) - 1] == ' ')
            {
                printf("\n");
            }
        }
    }
}

void find(const char *filename, const char ID[]) //find specific citizen by ID number and print it
{
    char citizen[400];
    char buf[100];
    char temp[100];
    int line = 1;
    int exist = 0;
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp_Check(fp))
    {
        if (does_exist(filename, ID) == 0)
        {
            printf("Citizen Does Not Exist\n");
            fclose(fp);
            return;
        }
    }
    while (fgets(buf, 100, fp) != NULL){
        if (buf[0] == '#' || buf[0] == '\n'){
            continue;
        }
        if (buf[0] == '-'){
            strcpy(citizen, temp);
            line = 1;
        }
        else{
            buf[strlen(buf) - 1] = '\0';
            if (line == 2){
                strcmp(buf, ID) == 0 ? exist = 1 : 0;
            }
            line++;
            strcat(buf, " ");
            strcat(citizen, buf);
            if (line == 4 && exist != 0){
                printf("%s", citizen);
                fclose(fp);
                return;
            }
        }
    }
}
