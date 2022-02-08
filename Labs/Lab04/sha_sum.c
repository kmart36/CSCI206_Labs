/*
 * Compute the sha256 sum of a file
 * Katy Martinson
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "sha256.h"

int main(int argc, char* argv[])
{
    if (argc < 2){
        // missing required file argument
        printf("Usage %s FILE\n", argv[0]);
        return(1);
    }

    SHA256_CTX hash;
    const int BS = 1024;

    unsigned char block[BS];

    sha256_init(&hash);
    
    int f = open (argv[1], O_RDONLY);
    if (f <  0){
        perror("error");
        return(2);
    }

    // TODO: Read from the file using the "read" function into "block"
    // pass all read data to sha256_update
    // repeat until you have processed the entire file

    // Pseudo code:
    // while ( read_block_from_file )
    //     sha256_update(&hash, block, bytes_read)
    
    // YOUR CODE BEGINS HERE
	size_t len = read(f, block, BS);
	while (len != 0) {
	  sha256_update(&hash, block, len);
	  len = read(f, block, BS); 
	}


    // YOUR CODE ENDS HERE
    // once you have read all of the file and passed it to sha256_update 
    // we have to call sha256_final to ensure the hash algorithm has 
    // processed all of the data.
    sha256_final(&hash, block);

    // now we can print the final hash, reusing the first SHA256_BLOCK_SIZE [32] bytes
    // of the data block buffer to hold the final hash value.
    for (int i=0; i < SHA256_BLOCK_SIZE; i++){
        printf("%02x", block[i]);
    }
    printf("  %s\n", argv[1]);

}
