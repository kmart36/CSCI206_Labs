/*
 * time.c
 */
#include <stdio.h>
#include <time.h>

extern void add_second(struct tm *);

int main(void)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
 
    printf ("it is now: %s\n", asctime(tm));
	for (int i = 0; i < 2345; i++) {
	  add_second(tm);
	}
    printf("+2345 seconds: %s\n", asctime(tm));
    return 0;
}
