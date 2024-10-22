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


int get_full_number(const char *text, int index) {

    int number = 0;

    int i = index;
    while (isdigit(text[i])) {
        i--;
    }
    i++;
    while (isdigit(text[i])) {
        number = number*10+text[i]-'0';
        ++i;
    }

    return number;
}


int main() {

    char *input = read_input(INPUT_SRC);

    // find line width
    char *first_nl = strstr(input, "\n");
    long width = first_nl-input+1; // +1 for '\n'

    int output = 0;

    int i = 0;
    char c;
    while (i < strlen(input)) {

        c = input[i];

        // find '*'s
        if (c == '*') {

            // check if adjacent chars are number or not
            int tl = ((i-width) > 0) && isdigit(input[i-width-1]);
            int t = ((i-width) >= 0) && isdigit(input[i-width]);
            int tr = ((i-width+1) > 0) && isdigit(input[i-width+1]);
            int r = ((i+1) < strlen(input)) && isdigit(input[i+1]);
            int br = ((i+width+1) < strlen(input)) && isdigit(input[i+width+1]);
            int b = ((i+width) < strlen(input)) && isdigit(input[i+width]);
            int bl = ((i+width-1) < strlen(input)) && isdigit(input[i+width-1]);
            int l = (i > 0) && isdigit(input[i-1]);

            int adjacent_count = 0;
            int n = 1;

            // check all possible patterns
            if (r) {
                adjacent_count++;
                n *= get_full_number(input, i+1);
            }
            if (l) {
                adjacent_count++;
                n *= get_full_number(input, i-1);
            }
            if (tr) {
                adjacent_count++;
                n *= get_full_number(input, i-width+1);
                if (!t && tl) {
                    adjacent_count++;
                    n *= get_full_number(input, i-width-1);
                }
            } else if (t) {
                adjacent_count++;
                n *= get_full_number(input, i-width);
            } else if (tl) {
                adjacent_count++;
                n *= get_full_number(input, i-width-1);
            }
            if (br) {
                adjacent_count++;
                n *= get_full_number(input, i+width+1);
                if (!b && bl) {
                    adjacent_count++;
                    n *= get_full_number(input, i+width-1);
                }
            } else if (b) {
                adjacent_count++;
                n *= get_full_number(input, i+width);
            } else if (bl) {
                adjacent_count++;
                n *= get_full_number(input, i+width-1);
            }

            if (adjacent_count == 2) {
                output += n;
            }
        }

        ++i;
    }

    free(input);

    printf("output: %d\n", output);

    return 0;
}