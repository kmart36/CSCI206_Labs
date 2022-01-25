/* Switchcase
 * Katy Martinson
 * Section 61
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
int main(){
    char string[256];   // store input string
     
    // this loop will read one line of input at a time
    // if EOF is reached, fgets() will return false, thus the loop will exit.
    while ( fgets(string, 256, stdin) ) { 
        /* use strlen and toupper in a loop to convert the string here */    
		for (int i = 0; i < strlen(string); i++) {
		  string[i] = toupper(string[i]);
		}
        // print the result
        printf("%s", string);
    }

    // C main programs return an error code. Typically 0 means “No errors.”
    return 0;
}
