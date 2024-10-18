#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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

    return input;
}


int main() {
    
    char *input = read_input(INPUT_SRC);

    // split lines
    char *line = strtok(input, "\n");
    int digit = -1, first = -1, last = -1;
    int total = 0;

    // for each line ...
    while (line != NULL) {

        // for each char find first and last digits
        for (int i = 0; i < strlen(line); ++i) {
            if (isdigit(line[i])) {
                // convert char digit to int
                digit = line[i] - '0';
                if (first == -1) first = digit;
            }
        }
        last = digit;

        // find line value and add to total values
        total += first*10+last;

        // set default
        digit = -1;
        first = -1;

        // iterate next line
        line = strtok(NULL, "\n");
    }

    free(input);

    printf("output: %d\n", total);
}