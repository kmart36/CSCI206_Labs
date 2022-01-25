/* Switchcase
 * <name>
 * <section>
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
int main(){
    char string[256];   // store input string
     
    // this loop will read one line of input at a time
    // if EOF is reached, fgets() will return false, thus the loop will exit.
    while ( fgets(/* you write this */) ){ 
        /* use strlen and toupper in a loop to convert the string here */    
 
        // print the result
        printf("%s", string);
    }

    // C main programs return an error code. Typically 0 means “No errors.”
    return 0;
}
