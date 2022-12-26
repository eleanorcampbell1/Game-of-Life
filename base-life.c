#include <stdio.h>
#include "life.h"

// You are only allowed to change the contents of this file with respect 
// to improving the performance of this program



// If you need to initialize some data structures for your implementation
// of life then make changes to the following function, otherwise 
// do not change this function.

void initLife() {
}

int life(long oldWorld[N][N], long newWorld[N][N]) {

    int i, j;
  
    //clear the new world
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    newWorld[j][i] = 0;
	}
    }

    int col, row;

    // Count the cells to the top left
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (i > 0 && j > 0) {
		row = j - 1;
		col = i - 1;
		newWorld[j][i] += oldWorld[row][col];
	    }
	}
    }
  
    // Count the cells immediately above
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (j > 0) {
		row = j - 1;
		col = i;
		newWorld[j][i] += oldWorld[row][i];
	    }
	}
    }

    // Count the cells to the top right
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (j > 0 && i < N - 1) {
		col = i + 1;
		row = j - 1;
		newWorld[j][i] += oldWorld[row][col];
	    }
	}
    }

    // Count the cells to the immediate left
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (i > 0) {
		col = i - 1;
		newWorld[j][i] += oldWorld[j][col];
	    }
	}
    }
  
    // Count the cells to the immediate right
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (i < N - 1) {
		col = i + 1;
		newWorld[j][i] += oldWorld[j][col];
	    }
	}
    }

    // Count the cells to the bottom left
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (i > 0 && j < N - 1) {
		col = i - 1;
		row = j + 1;
		newWorld[j][i] += oldWorld[row][col];
	    }
	}
    }

    // Count the cells immediately below
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (j < N - 1) {
		row = j + 1;
		newWorld[j][i] += oldWorld[row][i];
	    }
	}
    }

    // Count the cells to the bottom right
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (j < N - 1 && i < N - 1) {
		col = i + 1;
		row = j + 1;
		newWorld[j][i] += oldWorld[row][col];
	    }
	}
    }

    // Count the cells up two rows
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (j > 1) {
		row = j - 2;
		newWorld[j][i] += oldWorld[row][i];
	    }
	}
    }

    // Count the cells down two rows
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (j < N - 2) {
		row = j + 2;
		newWorld[j][i] += oldWorld[row][i];
	    }
	}
    }

    // Count the cells left two cols
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (i > 1) {
		col = i - 2;
		newWorld[j][i] += oldWorld[j][col];
	    }
	}
    }

    // Count the cells right two cols
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    if (i < N - 2) {
		col = i + 2;
		newWorld[j][i] += oldWorld[j][col];
	    }
	}
    }

    // Check each cell to see if it should come to life, continue to live, or die
    int alive = 0;
  
    for (i = 0; i < N; i++)
	for (j = 0; j < N; j++) {
	    newWorld[j][i] = checkHealth(newWorld[j][i], oldWorld[j][i]);
	    alive += newWorld[j][i] ? 1:0;
	}

    return alive;
}
