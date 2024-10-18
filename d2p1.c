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


int red_limit = 12;
int green_limit = 13;
int blue_limit = 14;


int main() {

    char *input = read_input(INPUT_SRC);

    // split lines
    char *p_line = input;
    char *line;
    int curr_line = 1;

    int curr_number = 0;
    char c;

    int red, green, blue;
    int impossible_games = 0;
    int i;

    // for each line ...
    while (line = strtok_r(p_line, "\n", &p_line)) {

        // get game content
        line = strstr(line, ":");
        line += 2;

        i = 0;
        red = 0; green = 0; blue = 0;
        // get color values of each set
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
                curr_number = 0;
            } else if (c == 'g') {
                // assign green and skip
                i += 5;
                green = curr_number;
                curr_number = 0;
            } else if (c == 'b') {
                // assign blue and skip
                i += 4;
                blue = curr_number;
                curr_number = 0;
            } else {
                // skip ", " chars
                i++;
            };

            // check if value exceed the limit,
            // if so, store the game number (line number)
            // by adding to impoosible_games
            if (red > red_limit ||
            green > green_limit ||
            blue > blue_limit) {

                impossible_games += curr_line;
                // if one color in one set and game exceeds the limit,
                // it is impossible anymore
                break;
            }
        }

        // iterate next line
        curr_line++;
    }

    free(input);

    // substract impossible game numbers from all games
    // and it is possible game numbers, the answer
    int output = ((curr_line-1)*curr_line/2)-impossible_games;

    printf("output: %d\n", output);

    return 0;
}