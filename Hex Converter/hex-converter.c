#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        int choice = 0;
        printf("Choose Convertion:\n|1| DEC to HEX\n|2| HEX to DEC\n|3| Exit\nChoice=> ");
        scanf("%d", &choice);
        int x;
        if (choice == 1)
        {
            printf("Decimal Number to Convert: ");
            scanf("%d", &x);
            printf("-----------------\n");
            printf("Dec\tHexa\n");
            printf("%d\t", x);
            printf("%X\n", x);
            printf("-----------------\n");
            getchar();
        }
        if (choice == 2)
        {
            printf("Hexadecimal Number to Convert: ");
            scanf("%X", &x);
            printf("-----------------\n");
            printf("Hexa\tDec\n");
            printf("%X\t", x);
            printf("%d\n", x);
            printf("-----------------\n");
            getchar();
        }
        if (choice != 1 && choice != 2)
        {
            printf("\n\nError! Please Choose 1 or 2, Then Perss 'ENTER'\n\n");
            getchar();
        }
    }

    return 0;
}
