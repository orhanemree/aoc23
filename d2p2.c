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

    // split lines
    char *p_line = input;
    char *line;
    int curr_line = 1;

    int curr_number;
    char c;

    int red, green, blue;
    int r_max, g_max, b_max;
    int i;
    int output = 0;

    // for each line ...
    while (line = strtok_r(p_line, "\n", &p_line)) {

        // get game content
        line = strstr(line, ":");
        line += 2;

        // set defaults
        curr_number = 0;
        i = 0;
        red = 0; green = 0; blue = 0;
        r_max = 0; g_max = 0; b_max = 0; 

        // get color values of each set and find max value
        while (i < strlen(line)) {
            c = line[i];
            if (isdigit(c)) {
                // get the numeric value
                curr_number = curr_number*10+(c-'0');
                i++;
            } else if (c == 'r') {
                // assign red and skip
                i += 3;
                red = curr_number;
                if (r_max < red) r_max = red;
                curr_number = 0;
            } else if (c == 'g') {
                // assign green and skip
                i += 5;
                green = curr_number;
                if (g_max < green) g_max = green;
                curr_number = 0;
            } else if (c == 'b') {
                // assign blue and skip
                i += 4;
                blue = curr_number;
                if (b_max < blue) b_max = blue;
                curr_number = 0;
            } else {
                // skip ", " chars
                i++;
            };
        }

        // find "power" of the game and add to output
        output += r_max*g_max*b_max;
    }

    free(input);

    printf("output: %d\n", output);

    return 0;
}