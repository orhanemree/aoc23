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


char digits[18][6] = {
    "one", "two", "three", "four",    
    "five", "six", "seven",    
    "eight", "nine",    
    "1", "2", "3", "4", "5", "6", "7", "8", "9"
};


int main() {
    
    char *input = read_input(INPUT_SRC);

    // split lines
    char *line = strtok(input, "\n");

    char *temp;
    int index = -1, min_index = 1024, max_index = -1;
    int first_value = -1, last_value = -1;
    int total = 0;

    // for each line ...
    while (line != NULL) {

        // check every digit if it exists or not
        for (int i = 0; i < sizeof(digits)/sizeof(digits[0]); ++i) {

            // find all digits
            temp = line;
            while (temp = strstr(temp, digits[i])) {

                // find index of digit
                index = temp - line;
                temp++;

                // if it is possible first or last digit, store it's index
                // and numeric value
                if (min_index > index) {
                    min_index = index;
                    first_value = (i%9)+1; // by the order of digits array
                }

                if (max_index < index) {
                    max_index = index;
                    last_value = (i%9)+1; // by the order of digits array
                }
            }
        }

        // find line value and add to total values
        total += first_value*10+last_value;

        // set default
        index = -1;
        min_index = 1024;
        max_index = -1;
        first_value = -1; last_value = -1;

        // iterate next line
        line = strtok(NULL, "\n");
    }

    free(input);

    printf("output: %d\n", total);
}