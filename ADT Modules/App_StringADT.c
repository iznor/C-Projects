#include "stringADT.h"

int main(){
    int index=3;
    char c='C';
    CASE e_lowercase=LOWER_CASE;
    String s1,s2,s3,s4,s5,s6;

    //Creates new string s1 with given C string
    s1=string_create("ABC");
    //Prints the char string and the length of s1 string
    printf("String s1: %s\n length s1: %d\n\n",string_chars(s1),string_length(s1));

    //Creates new string s2 by given string s3 and the amount of times to copy it
    printf("S1: ");
    string_print(s1);
    printf("S2 after creation by multString func(using mult S1 3 times)->");
    s2=multString_create(s1,3);
    string_print(s2);


    //Creates a new copy s3 of s2
    printf("\nS2: ");
    string_print(s2);
    printf("S3 after creation by duplicating S2-> ");
    s3=string_dup(s2);
    string_print(s3);


    //Prints the char from s3 string for the given index 
    printf("\nIn S3: %s the char in index %d is: ", string_chars(s3), index);
    printf("%c\n",string_charByIndex(s3,index));
    //Prints the index from s3 string for the given char 
    printf("In S3: %s the first index of char %c is: ", string_chars(s3), c);
    printf("%d\n\n",string_findIndexByChar(s3,c));

    //Prints if the string s2,s3 are equal or not
    printf("S2: ");
    string_print(s2);
    printf("S3: ");
    string_print(s3);
    printf("The Strings S2 and S3 are: %s\n\n",string_isEqual(s2,s3)?"Equal":"Not Equal");

    printf("S1: ");
    string_print(s1);
    printf("S2: ");
    string_print(s2);
    printf("The Strings S1 and S2 are: %s\n\n", string_isEqual(s1,s2)?"Equal":"Not Equal");

    s4=string_create("123abc");
    printf("S4: ");
    string_print(s4);
    //Add s4 to s1
    printf("S1: %s after adding the string S4: %s -> new S1: ", string_chars(s1), string_chars(s4));
    s1=string_addString(s1,s4);
    string_print(s1);

    //Copy the chars in s4 to s3
    printf("\nS3: %s after copying the chars in the string S4: %s -> new S3: ",string_chars(s3), string_chars(s4));
    s3=string_copy(s3,s4);
    string_print(s3);

    //Change the UPPER letters to lower letters
    printf("\nS3: %s after using convertCase func -> new S3: ", string_chars(s3));  
    string_convertCase(s3,e_lowercase);
    string_print(s3);

    s5=string_create("abc");
    printf("\nS5: ");
    string_print(s5);
    //Prints the index of string s5 in the string s3
    printf("In S3: %s the index of the first appearance of S5: %s is: ", string_chars(s3),string_chars(s5));
    printf("%d\n\n",string_findString(s3,s5));

    //Remove from s4 the string s5 
    printf("S4: %s after removing S5: %s -> new S4: ", string_chars(s4),string_chars(s5));
    string_removeString(s4,s5);
    string_print(s4);

    //Prints if the string s4 contains only digits
    printf("\nThe String S4: %s %s all digits\n\n",string_chars(s4),string_isAllDigits(s4)?"is":"is not");

    s6=string_create("aaa, bbb. ccc: ddd?");
    printf("S6: ");
    string_print(s6);	
    STRING_FOREACH(word,s6){
            printf("word: ");
            string_print(word);
            string_destroy(word);
    }

    string_destroy(s1);    string_destroy(s2);
    string_destroy(s3);    string_destroy(s4);
    string_destroy(s5);    string_destroy(s6);
}
