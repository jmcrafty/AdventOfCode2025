#include <stdio.h>
#include <stdlib.h>

// Must change this value
#define GRID_SIZE 10

int grid[GRID_SIZE][GRID_SIZE] = {0};
int rolls = 0;

void print_grid() {
    // print the output
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

void count_grid() {
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y] < 4 && grid[x][y] != -1) {
                rolls++;
            }
        }
    }
}

int clear_grid() {
    int cleared = 0;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y] < 4 && grid[x][y] != -1) {
                grid[x][y] = -1;
                cleared = 1;
            }
        }
    }
}

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

void parse_file() {
    FILE *fp;
    char line[256];
    int x = 0, y = 0;

    // open file for read only
    fp = fopen("4_test.txt", "r");
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

void parse_grid() {
    char line[256];
    int x = 0, y = 0;

    // open file for read only
    for (y = 0; y < GRID_SIZE; y++) {
        for (x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y] != -1) {
                space_counter(x, y);
            }
        }
    }
}


int main() {
    parse_file();
    print_grid();
    count_grid();
    clear_grid();
    parse_grid();
    printf("\r\n");
    print_grid();
    count_grid();
    printf("rolls: %i\r\n", rolls);
    return 0;
}