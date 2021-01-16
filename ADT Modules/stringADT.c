#include "stringADT.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct _string
{
    char *data;
    int length;
    int capacity;
    int iterator;
};

//ORIGINAL FUNCTIONS

String string_create(char *s)
{
    int length=strlen(s);
    int capacity=length+1;
    String new=(String)malloc(sizeof(struct _string));
    new->data=(char*)malloc(capacity);
    if (new==NULL || new->data==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }

    strcpy(new->data,s);
    new->length=length;
    new->capacity=capacity;
    return new;
}

String multString_create(String s, int times)
{
    assert(s!=NULL);
    if (times<0){
        fprintf(stderr, "%s", "multiplication error\n");
        return NULL;
    }
    int new_length=times*(s->length);
    int new_capacity=new_length+1;
    char temp[new_capacity];
    String new=(String)malloc(sizeof(struct _string));
    new->data=(char*)malloc(new_capacity);
    if (new==NULL || new->data==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }
    //--------------------------------------
    strcpy(temp,s->data);
    for (int i = 0; i < times-1; i++){
        strcat(temp,s->data);
    }
    new->capacity=new_capacity;
    new->length=new_length;
    strcpy(new->data, temp);
    return new;
}

void string_destroy(String s)
{
    assert(s!=NULL);
    free(s->data);
    free(s);
    return;
}

int string_length(String s)
{
    assert(s!=NULL);
    int length=strlen(s->data);
    if (length<=0){
        fprintf(stderr, "%s", "error\n");
        return -1;
    }

    return length;
}

char* string_chars(String s)
{
    assert(s!=NULL);
    return s->data;
}

String string_dup(String s)
{
    assert(s!=NULL);
    String new=(String)malloc(sizeof(struct _string));
    new->data = (char*)malloc(s->capacity);
    if (new==NULL || new->data==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }
    new->length=s->length;
    new->capacity=s->capacity;
    strcpy(new->data, s->data);
    return new;
}

char string_charByIndex(String s, int index) 
{
    assert(s!=NULL);
    if (index<0 || index>strlen(s->data)){
        fprintf(stderr, "%s", "index error\n");
        return '\0';
    }
    
    return s->data[index];
}

int string_findIndexByChar(String s, char c) 
{
    assert(s!=NULL);
    int index=-1;
    int size=strlen(s->data);
    for (int i = 0; i < size; i++){
        if (s->data[i]==c){
            index=i;
            break;
        }
    }
    return index;
}

bool string_isEqual(String s1, String s2)
{
    assert(s1 !=NULL && s2!=NULL);
    if (strcmp(s1->data,s2->data)==0){
        return true;
    }
    
    return false;
}

String string_addString(String dest, String src)
{
    assert(dest!=NULL && src!=NULL);
    int length_src=strlen(src->data);
    int capacity_src=length_src+1;
    int length_dest=strlen(dest->data);
    int capacity_dest=length_dest+1;
    int length_both=length_dest+length_src;
    int capacity_both=capacity_dest+capacity_src;
    //--------------------------------------------
    if (capacity_dest<capacity_both)
    {
        dest->data = (char*)realloc(dest->data ,capacity_both);
        if (dest->data==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }
    }
    
    dest->length=length_both;
    dest->capacity=capacity_both;
    strcat(dest->data, src->data);
    return dest;
}

String string_copy(String dest, String src)
{
    assert(dest!=NULL && src!=NULL);
    int length_src=strlen(src->data);
    int capacity_src=length_src+1;
    int length_dest=strlen(dest->data);
    int capacity_dest=length_dest+1;
    
    if (capacity_dest < capacity_src){
        dest->data = (char*)realloc(dest->data ,capacity_src);
        if (dest->data==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }
        strcpy(dest->data,src->data);
        dest->capacity=capacity_src;
        dest->length=length_src;
        return dest;
    }
    
    for (int i = 0; i < length_src; i++){
        dest->data[i]=src->data[i];
    }
    return dest;
}

String string_convertCase(String s, CASE ul)
{
    assert(s!=NULL);
    if (ul!=UPPER_CASE && ul!=LOWER_CASE){
        fprintf(stderr, "%s", "CASE error\n");
    }
    
    if (ul==UPPER_CASE){
        strupr(s->data);
    }

    if (ul==LOWER_CASE){
        strlwr(s->data);
    }

    return s;
}

bool string_isAllDigits(String s)
{
    assert(s!=NULL);
    for (int i = 0; i < s->length; i++)
        if (s->data[i]<'0' || s->data[i]>'9')
            return false;  
    return true;
}

int string_findString(String dest, String sub_str)
{
    assert(dest!=NULL && sub_str!=NULL);
    char src[dest->capacity];
    char dst[sub_str->capacity];
    char *p_dst;
    strcpy(src,dest->data);
    strcpy(dst,sub_str->data);
    p_dst=strstr(src,dst);
    int index = p_dst-src;
    if (index<0){
        index -1;
    }
    return index;
}

String string_removeString(String dest, String sub_str)
{
    assert(dest!=NULL && sub_str!=NULL);
    int length_new=dest->length-sub_str->length;
    int capacity_new=length_new+1;
    char *data_new=(char*)malloc(capacity_new);     //free in line 257
    assert(data_new!=NULL);
    int sub_index=string_findString(dest,sub_str);
    for (int i = 0; i < sub_index; i++)
    {
        data_new[i]=dest->data[i];
    }
    int j=sub_index;
    for (int i = sub_index+sub_str->length; i < dest->length; i++)
    {
        data_new[j]=dest->data[i];
        j++;   
    }
    dest->data=(char*)realloc(dest->data, capacity_new);
    if (dest->data==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }
    strcpy(dest->data,data_new);
    dest->length=length_new;
    dest->capacity=capacity_new;
    free(data_new);
    return dest;
}

void string_print(String s)
{
    assert (s!=NULL);
    printf("%s \n", s->data);
    return;
}

// BONUS $ $ $ //

String string_GetNext(String s)
{
    assert (s!=NULL);
    //set the iterator to the index of the next word
    while (s->data[s->iterator]== ' '){
        ++s->iterator;
    }
    int i=0;
    int length=0;
    int curr=s->iterator;
    //get the length of the next word
    while (s->data[curr]!= ' '){
        if (s->data[curr]=='\0'){
            break;
        }
        ++length;
        ++curr;
    }
    //set an array of chars with a size = length we found
    
    //temporary solution
    char *word=(char*)malloc((length+1));
    if (word==NULL){
        fprintf(stderr, "%s", "allocation error\n");
        return NULL;
    }

    while (s->data[s->iterator]!=' '){
        word[i]=s->data[s->iterator];
        ++s->iterator;
        ++i;
        if (s->data[s->iterator]=='\0'){
            break;
        }
    }
    //now the array of chars contains the next word
    //create a new 'String' and initialize it with the array wev'e made
    String next_word = string_create(word);
    free(word);
    //set the iterator to the index of the end of the word
    while (s->data[s->iterator]== ' '){
        s->iterator++;
        if (s->data[s->iterator]== '\0'){
            break;
        }
    }
    //return String next_word
    return next_word;
}

String string_GetFirst(String s)
{
    assert (s!=NULL);
    s->iterator=0;
    string_GetNext(s);
}

bool string_IsDone(String s)
{
    assert (s!=NULL);
    //if the iterator reached the index of the end of the last word - the string is done.
    if (s->iterator== s->capacity)
    {
        return true;
    }
    return false;
}
