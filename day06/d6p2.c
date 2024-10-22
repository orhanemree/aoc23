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

    // find distance
    long distance = 0;
    for (int i = 1; i <= strlen(distance_line); ++i) {
        char c = distance_line[i];
        if (isdigit(c)) {
            if (distance == 0) {
                distance = c-'0'; // convert char to int
            } else {
                distance = distance*10+c-'0';
            }
        }
    }

    // find time
    long time = 0;
    for (int i = 0; i < strlen(distance_line); ++i) {
        char c = input[i];
        if (isdigit(c)) {
            if (time == 0) {
                time = c-'0'; // convert char to int
            } else {
                time = time*10+c-'0';
            }
        }
    }

    // calculate possible ways
    int way_count = 0;
    for (int s = 0; s < time; ++s) {
        // s: holded miliseconds
        long curr_distance = (time-s)*s;
        if (curr_distance > distance) {
            // win condition
            way_count++;
        }
    }

    printf("output: %d\n", way_count);

    free(input);

    return 0;
}