#include <stdio.h>
#include <string.h>
#include "life.h"

// You are only allowed to change the contents of this file with respect 
// to improving the performance of this program

#define BIRTH 3
#define TOOCROWDED 4
#define TOOEMPTY 2

// If you need to initialize some data structures for your implementation
// of life then make changes to the following function, otherwise 
// do not change this function.

void initLife() {
}
inline int sumNeighborsNoChecks(long oldWorld[N][N], int j, int i, long cache[3], long otherTwo){

	register long newCell = oldWorld[j - 2][i]; 		//two left
	long oldCellValue = oldWorld[j][i];
	newCell += oldWorld[j][i - 2]; 						//two up
	newCell += oldWorld[j][i - 1]; 					//one up
	newCell += oldWorld[j][i + 2]; 					//two below
	newCell += oldWorld[j][i + 1]; 						//bottom
	newCell += oldWorld[j + 2][i]; 						//two right
	newCell += otherTwo;
	
	newCell += cache[0];
	newCell += cache[1];
	newCell += cache[2];

	if((newCell == BIRTH) || (oldCellValue && (newCell == TOOEMPTY))){
		newCell = 1;
	}else{
		newCell = 0;
	}

	return newCell;
	
}
inline int sumNeighborsWithChecksTopRow(long oldWorld[N][N], int j, int i){
	register long newCell = 0;
	if (j > 0) {
		if (j > 1) {
			newCell += oldWorld[j - 2][i]; 		//two above
		}
		if(i > 0){
			newCell += oldWorld[j - 1][i-1]; 	//top left
		}
		newCell += oldWorld[j - 1][i+1]; 	//top right
		newCell += oldWorld[j - 1][i]; 			//top
	    }

		long oldCellValue = oldWorld[j][i];
		if (i > 0) {
			newCell += oldWorld[j][i - 1]; 		//left cell
	    }
		newCell += oldWorld[j][i + 2]; 			//two right
		newCell += oldWorld[j][i + 1]; 			//right cell
		
	    if (j < N - 1) {
			if (j < N - 2) {
				newCell += oldWorld[j + 2][i]; 		//two below
	    	}
			if(i > 0){								//bottom left
				newCell += oldWorld[j + 1][i - 1];
			}
			newCell += oldWorld[j + 1][i + 1]; 	//bottom right
			newCell += oldWorld[j + 1][i]; 			//bottom cell
	    }

		if((newCell == BIRTH) || (oldCellValue && (newCell == TOOEMPTY))){
			newCell = 1;
		}else{
			newCell = 0;
		}

		return newCell;

}
inline int sumNeighborsWithChecksBottomRow(long oldWorld[N][N], int j, int i){
	register long newCell = 0;
	if (j > 0) {
		if (j > 1) {
			newCell += oldWorld[j - 2][i]; 		//two above
		}
		newCell += oldWorld[j - 1][i-1]; 	//top left

		if(i < N - 1){
			newCell += oldWorld[j - 1][i+1]; 	//top right
		}
		newCell += oldWorld[j - 1][i]; 			//top
	    }	
		long oldCellValue = oldWorld[j][i];
		newCell += oldWorld[j][i - 2]; 	//two left
		newCell += oldWorld[j][i - 1]; 		//left cell

		if (i < N - 1) {
			newCell += oldWorld[j][i + 1]; 		//right cell
	    }
	    if (j < N - 1) {
			newCell += oldWorld[j + 1][i - 1];
			if(i < N - 1) {							
				newCell += oldWorld[j + 1][i + 1]; 	//bottom right
			}
			newCell += oldWorld[j + 1][i]; 			//bottom cell
			if (j < N - 2) {
				newCell += oldWorld[j + 2][i]; 		//two below
	    	}
	    }
		if((newCell == BIRTH) || (oldCellValue && (newCell == TOOEMPTY))){
			newCell = 1;
		}else{
			newCell = 0;
		}
		return newCell;

}
inline int sumNeighborsWithChecksRightCol(long oldWorld[N][N], int j, int i){

		register long newCell = oldWorld[j - 2][i]; 			//two above
		newCell += oldWorld[j - 1][i-1]; 			//top left
		newCell += oldWorld[j - 1][i+1]; 			//top right
		newCell += oldWorld[j - 1][i]; 				//top
		long oldCellValue = oldWorld[j][i];
		newCell += oldWorld[j][i - 2]; 				//two left
		newCell += oldWorld[j][i - 1]; 				//left cell

		if (i < N - 1) {
			newCell += oldWorld[j][i + 2]; 	//two right
			newCell += oldWorld[j][i + 1]; 		//right cell
	    }
	    if (j < N - 1) {						//bottom left
			newCell += oldWorld[j + 1][i - 1];
			newCell += oldWorld[j + 1][i + 1]; 	//bottom right
			newCell += oldWorld[j + 1][i]; 		//bottom cell
	    }
		if((newCell == BIRTH) || (oldCellValue && (newCell == TOOEMPTY))){
			newCell = 1;
		}else{
			newCell = 0;
		}

		return newCell;
}

inline int sumNeighborsWithChecksLeftCol(long oldWorld[N][N], int j, int i){
	register long newCell = 0;
	if (j > 0) {
		newCell += oldWorld[j - 1][i-1]; 		//top left
		newCell += oldWorld[j - 1][i+1]; 		//top right
		newCell += oldWorld[j - 1][i]; 			//top
	    }	
		long oldCellValue = oldWorld[j][i];
		newCell += oldWorld[j][i - 2]; 			//two left
		newCell += oldWorld[j][i - 1]; 			//left cell
		newCell += oldWorld[j][i + 2]; 			//two right
		newCell += oldWorld[j][i + 1]; 			//right cell
		newCell += oldWorld[j + 1][i - 1];
		newCell += oldWorld[j + 1][i + 1]; 		//bottom right
		newCell += oldWorld[j + 1][i]; 			//bottom cell
		newCell += oldWorld[j + 2][i]; 			//two below
		if((newCell == BIRTH) || (oldCellValue && (newCell == TOOEMPTY))){
			newCell = 1;
		}else{
			newCell = 0;
		}
		return newCell;

}

int life(long oldWorld[N][N], long newWorld[N][N]) {
    register int i, j;
	register long newCell = 0;	
	register int alive = 0;

	// top 2 rows
	for(j = 0; j < N; j++){
		for(i = 0; i <= 1; i++){
			newCell = sumNeighborsWithChecksTopRow(oldWorld, j, i);

			alive += newCell;
			newWorld[j][i] = newCell;
		}
	}
	// bottom 2 rows
	for(j = 0; j < N; j++){
		for(i = (N-2); i <= (N-1); i++){
			newCell = sumNeighborsWithChecksBottomRow(oldWorld, j, i);
			
			alive += newCell;
			newWorld[j][i] = newCell;
		}
	}

	// left 2 columns (dont repeat top/bottom 2 rows)
	for(j = 0; j <= 1; j++){
		for(i = 2; i < (N-2); i++){
			newCell = sumNeighborsWithChecksLeftCol(oldWorld, j, i);

			alive += newCell;
			newWorld[j][i] = newCell;
		}
	}

	// right 2 columns (dont repeat top/bottom 2 rows)
	for(j = (N-2); j < N; j++){
		for(i = 2; i < (N-2); i++){
			newCell = sumNeighborsWithChecksRightCol(oldWorld, j, i);

			alive += newCell;
			newWorld[j][i] = newCell;
		}
	}

	long cache[3];
	register long otherTwo;
	// middle (2in)
	for(j = 2; j < (N-2); j++){
		//build cache
		i = 2;
		register int topPos = 0;
		cache[0] = oldWorld[j - 1][1] + oldWorld[j + 1][1];			//set top position
		cache[1] = oldWorld[j - 1][2] + oldWorld[j + 1][2];			//set middle position
		cache[2] = oldWorld[j - 1][3] + oldWorld[j + 1][3];			//set bottom position
		//otherTwo = (oldWorld[j][i + 2]); 		//
		otherTwo = 0;
		for(i = 2; i < (N-2); i++){
			newCell = sumNeighborsNoChecks(oldWorld, j, i, cache, otherTwo);
			alive += newCell;
			newWorld[j][i] = newCell;

			//update cache
			cache[topPos] = oldWorld[j-1][i+2] + oldWorld[j+1][i+2];
			
			//update position
			topPos = (topPos + 1) % 3;
		}
	}

	return alive;
}