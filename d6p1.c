#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define INPUT_SRC "./input.txt"


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

    char *distance_line = strstr(input, "\n");

    int output = 1;

    // split distances
    int curr_number = 0;
    int distances[10] = {0};
    int distances_len = 0;
    for (int i = 1; i <= strlen(distance_line); ++i) {
        char c = (distance_line)[i];
        if (isdigit(c)) {
            if (curr_number == 0) {
                curr_number = c-'0'; // convert char to int
            } else {
                curr_number = curr_number*10+c-'0';
            }
        } else if (curr_number && (c == ' ' || i == strlen(distance_line) /*EOF*/)) {
            distances[distances_len++] = curr_number;
            curr_number = 0;
        }
    }

    // split times and calculate possible ways
    int times_len = 0;
    int way_count = 0;
    for (int i = 0; i < strlen(distance_line); ++i) {
        char c = input[i];
        if (isdigit(c)) {
            if (curr_number == 0) {
                curr_number = c-'0'; // convert char to int
            } else {
                curr_number = curr_number*10+c-'0';
            }
        } else if (curr_number && (c == ' ' || c == '\n')) {

            // calculate possible ways count
            for (int s = 0; s < curr_number; ++s) {
                // s: holded miliseconds
                int distance = (curr_number-s)*s;
                if (distance > distances[times_len]) {
                    // win condition
                    way_count++;
                }
            }

            // multiply with current output
            output *= way_count;
            times_len++;

            // defaults
            way_count = 0;
            curr_number = 0;
        }
    }

    printf("output: %d\n", output);

    free(input);

    return 0;
}