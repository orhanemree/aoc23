#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INPUT_SRC "./input.txt"
#define MAX_INPUT 4096


char *read_input(const char *src) {

    FILE *f = fopen(src, "rb");

    // get size of the input file
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *input = malloc(fsize+1);

    // read file
    fread(input, fsize, 1, f);
    input[fsize] = 0;

    fclose(f);

    // free(input) after use
    return input;
}