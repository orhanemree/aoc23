#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define INPUT_SRC "./input.txt"
#define MAX_SEEDS_SIZE 20


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

    // a kind of tuple that holds (seed_number and stage_of_seed)
    long seeds[MAX_SEEDS_SIZE][2];
    int seed_count = 0;
    int curr_stage = 0;

    // iterate each line
    char *line = strtok(input, "\n");
    int curr_line = 0;
    int width = strlen(line);
    while (line != NULL) {

        if (curr_line == 0) {
            // it is the seeds line
            // parse seeds
            char *save_p;
            char *seed_tok = strtok_r(line, " ", &save_p);
            int curr_seed = 0;

            while (seed_tok != NULL) {

                // skip first token "seeds: " and start with numeric seeds directly
                if (seed_tok[0] != 's') {
                    long seed = strtol(seed_tok, NULL, 10);
                    seeds[curr_seed][0] = seed;
                    seeds[curr_seed][1] = curr_stage; // or basicly 0
                    ++curr_seed;
                    ++seed_count;
                }

                seed_tok = strtok_r(NULL, " ", &save_p);
            }
        } else if (line[0] == '\n') {
            // pass
        } else if (isalpha(line[0])) {
            curr_stage++;
        } else {
            // it is map line, split it
            long destination_start, source_start, range;
            sscanf(line, "%ld %ld %ld", &destination_start, &source_start, &range);
            // check every seed and convert the number
            for (int i = 0; i < seed_count; ++i) {
                // make sure convert a seed one time in one map
                if (seeds[i][1] < curr_stage) {
                    // check if seed is between the range, if yes, change it
                    if (seeds[i][0] >= source_start && seeds[i][0] <= source_start+range) {
                        seeds[i][0] = seeds[i][0]-source_start+destination_start;
                        seeds[i][1] = curr_stage;
                    }
                }
            }
        }

        // next line
        curr_line++;
        line = strtok(NULL, "\n");
    }

    // find lowest
    long lowest = seeds[0][0];
    for (int i = 1; i < seed_count; ++i) {
        if (seeds[i][0] < lowest) {
            lowest = seeds[i][0];
        }
    }

    printf("output: %ld\n", lowest);

    free(input);

    return 0;
}