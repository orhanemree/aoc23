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

    // free(input) after use
    return input;
}


int main() {

    char *input = read_input(INPUT_SRC);

    // find line width
    char *first_nl = strstr(input, "\n");
    long width = first_nl-input+1; // +1 for '\n'

    int curr_num = 0;
    int valid = 1;

    int output = 0;

    int i = 0;
    char c;
    while (i < strlen(input)) {

        c = input[i];

        if (c == '.' || c == '\n') {
            if (curr_num) {
                // there was a digit previously
                // check last digit's adjacent

                // check top right
                if (valid &&
                (((i-width) > 0 ? (input[i-width] == '.' || input[i-width] == '\n') : 1) &&
                // check bottom right
                ((i+width) < strlen(input) ? (input[i+width] == '.' || input[i+width] == '\n') : 1))) {
                    // valid
                } else {
                    valid = 0;
                }
            }

            if (!valid) {
                output += curr_num;
            }

            // default setup
            curr_num = 0;
            valid = 1;
        }

        else if (isdigit(c)) {

            if (curr_num == 0) {
                // the beginning of number
                // check adjacent

                // check left
                if ((i > 0 ? (input[i-1] == '.' || input[i-1] == '\n') : 1) &&
                // check top left
                ((i-width) > 0 ? (input[i-width-1] == '.' || input[i-width-1] == '\n') : 1) &&
                // check bottom left
                ((i+width-1) < strlen(input) ? (input[i+width-1] == '.' || input[i+width-1] == '\n') : 1)) {
                    // valid
                } else {
                    valid = 0;
                }
            }

            // not beginnig of number
            // check top
            if (valid && (((i-width) >= 0 ? (input[i-width] == '.' || input[i-width] == '\n') : 1) &&
            // check bottom
            ((i+width) < strlen(input) ? (input[i+width] == '.' || input[i+width] == '\n') : 1))) {
                // valid
            } else {
                valid = 0;
            }

            curr_num = curr_num*10+(c-'0');
        }

        // other chars
        else {
            if (curr_num) {
                // there was a digit previously
                // it is invalid since right (currrent char) is invalid
                valid = 0;

                if (!valid) {
                    output += curr_num;
                }

                // default setup
                curr_num = 0;
                valid = 1;
            } else {
                // pass
            }
        }

        ++i;
    }

    free(input);

    printf("output: %d\n", output);

    return 0;
}