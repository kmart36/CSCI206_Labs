/*
 * double.c
 */
#include <stdio.h>
#include <stdlib.h>

int double_value(int n);

int main (int argc, char* argv[])
{
    int i, n = 0, maxnum = 80;
    if (argc > 1){
      maxnum = atoi(argv[1]);
    }
    printf("Double the value from 0 to %d\n", maxnum - 1);
    for (i = 0; i < maxnum; i++){
        n = double_value(i);
        printf("%-7d", n);
        if (((i+1) % 10) == 0){
            printf("\n");
        }
    }
    
    return 0;
}

