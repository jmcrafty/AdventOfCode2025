#include <stdio.h>
#include <stdlib.h>

// Must change this value
#define GRID_SIZE 135

int grid[GRID_SIZE][GRID_SIZE] = {0};
int rolls = 0;


// add counters to each space around the roll
void space_counter(int x_pos, int y_pos) {
    for (int y = y_pos - 1; y <= y_pos + 1; y++) {
        for (int x = x_pos - 1; x <= x_pos + 1; x++) {
            // out of bounds
            if (x < 0 || y < 0 || x >= GRID_SIZE || y >= GRID_SIZE) {
                continue;
            }
            // skip self
            if (x == x_pos && y == y_pos) {
                continue;
            }
            // skip empty spots
            if (grid[x][y] == -1) {
                continue;
            }
            // increment counter
            grid[x][y]++;
        }
    }
}

// remove the unblocked paper and reset the counters
int clear_grid() {
    // flag
    int cleared = 0;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y] < 4) {
                if (grid[x][y] != -1) {
                    grid[x][y] = -1;
                    rolls++;
                    cleared = 1;
                }
            } else {
                grid[x][y] = 0;
            }
        }
    }
    return cleared;
}


// open the file to fill the grid while also doing the first parse
void parse_file() {
    FILE *fp;
    char line[256];
    int x = 0, y = 0;

    // open file for read only
    fp = fopen("4_input.txt", "r");
    while (fgets(line, sizeof(line), fp) != NULL) {
        for (x = 0; x < GRID_SIZE; x++) {
            if (line[x] == '@') {
                space_counter(x, y);
            }
            if (line[x] == '.') {
                grid[x][y] = -1;
            }
        }
        y++;
    }
}

// execute counters on the spaces with paper rolls
void parse_grid() {
    int x = 0, y = 0;
    for (y = 0; y < GRID_SIZE; y++) {
        for (x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y] != -1) {
                space_counter(x, y);
            }
        }
    }
}


void print_grid() {
    // print the formatted output
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y] >= 4) {
                printf("@ ");
            } else if (grid[x][y] == -1) {
                printf(". ");
            } else {
                printf("x ");
            }
        }
        printf("\r\n");
    }
}


int main() {
    parse_file();
    while (clear_grid()) {
        parse_grid();
    }
    //print_grid();
    printf("rolls: %i\r\n", rolls);
    return 0;
}