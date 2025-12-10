// insertion sort ranges
// merge ranges
// sort inputs
// 
// iterate over inputs
//     count values in range

#include <stdio.h>  // printf, NULL
#include <string.h>
#include <stdlib.h> // strtoull

#define u64_t unsigned long long
#define MAX_RANGES 256

u64_t ranges[MAX_RANGES][2] = {0};
int counter = 0;
u64_t sum = 0;


void parse_file() {
    FILE *fp;
    char line[256];
    int input_flag = 0;
    int good = 0;
    u64_t lower, upper;
    fp = fopen("5_input.txt", "r");
    while (fgets(line, sizeof(line), fp) != NULL) {
        // blank line (or last line)
        if (strlen(line) <= 1) {
            break;
        }

        // if theres a dash its a range
        char* str_ptr = strchr(line, '-');
        if (str_ptr == NULL) {
            // no dash its an input
            continue;
        }
        // split range into upper and lower
        upper = strtoull(str_ptr + 1, NULL, 10);
        *str_ptr = '\0';
        lower = strtoull(line, NULL, 10);
        
        ranges[counter][0] = lower;
        ranges[counter][1] = upper;
        counter++;
    }
}


void list_merge() {
    int merge_flag = 1;
    while (merge_flag) {
        merge_flag = 0;
        // iterate over elements at the end of the list
        for (int i = counter; i > 0; i--) {
            // skip merged elements
            if (ranges[i][0] == 0 && ranges[i][1] == 0) {
                continue;
            }
            // compare the range to ranges above it
            for (int j = 0; j < counter; j++) {
                if (i == j) continue;
                // lower is within existing range
                if (ranges[i][0] >= ranges[j][0] && ranges[i][0] <= ranges[j][1]) {
                    // check if upper is greater than other upper
                    if (ranges[i][1] > ranges[j][1]) {
                        ranges[j][1] = ranges[i][1];
                    }
                    ranges[i][0] = 0;
                    ranges[i][1] = 0;
                    merge_flag = 1;
                    break;
                }
                // upper is within existing range
                if (ranges[i][1] >= ranges[j][0] && ranges[i][1] <= ranges[j][1]) {
                    if (ranges[i][0] < ranges[j][0]) {
                        ranges[j][0] = ranges[i][0];
                    }
                    ranges[i][0] = 0;
                    ranges[i][1] = 0;
                    merge_flag = 1;
                    break;
                }
            }
        }
    }
}


void count_ranges() {
    sum = 0;
    for (int i = 0; i < counter; i++) {
        // skip merged elements
        if (ranges[i][0] == 0 && ranges[i][1] == 0) {
            continue;
        }
        // get the number of elements in the range inclusive
        sum += (ranges[i][1] - ranges[i][0]) + 1ULL;
    }
}


int main() {
    parse_file();
    list_merge();
    count_ranges();
    printf("sum: %llu\r\n", sum);
    return 0;
}