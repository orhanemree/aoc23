#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INPUT_SRC "./input.txt"
#define MAX_QUEUE_SIZE 20


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

    int output = 0;

    int queue[MAX_QUEUE_SIZE] = {0};

    // iterate each line
    char *line = strtok(input, "\n");
    long width = strlen(line);
    while (line != NULL) {

        // find position of char '|'
        char *temp = strstr(line, "|");
        long delim_pos = temp-line;

        // find count of winning numbers
        temp = strstr(line, ":");
        long winning_count = (delim_pos-(temp-line)-2)/3;

        // find count of other numbers to check
        long other_numbers_count = (width-delim_pos)/3;

        // find winnig numbers
        int winnings[winning_count];
        for (int i = 0; i < winning_count; ++i) {
            // find numeric value
            if (line[delim_pos-i*3-3] == ' ') {
                // one figure number
                winnings[i] = (line[delim_pos-i*3-2]-'0');
            } else {
                // two figures number
                winnings[i] = (line[delim_pos-i*3-3]-'0')*10+(line[delim_pos-i*3-2]-'0');
            }
        }

        // get the count of copies of this card from queue
        int curr_cards = queue[0]+1;
        output += curr_cards;

        // shift queue
        for (int j = 0; j < MAX_QUEUE_SIZE-1; ++j) {
            queue[j] = queue[j+1];
        }

        int point = 0;

        // find other numbers and check whether they are winning
        for (int i = 0; i < other_numbers_count; ++i) {
            int n;
            // find number
            if (line[delim_pos+i*3+2] == ' ') {
                // one figure number;
                n = line[delim_pos+i*3+3]-'0';
            } else {
                // two figures number
                n = (line[delim_pos+i*3+2]-'0')*10+(line[delim_pos+i*3+3]-'0');
            }

            // check winning and increment next cards copy count in queue
            for (int i = 0; i < winning_count; ++i) {
                if (winnings[i] == n) {
                    // add copy for next cards
                    queue[point] += curr_cards;
                    point++;
                    break;
                }
            }
        }

        // next line
        line = strtok(NULL, "\n");
    }

    free(input);

    printf("output: %d\n", output);

    return 0;
}