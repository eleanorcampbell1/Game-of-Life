#ifndef LIFE_H

#define LIFE_H 1

#define N (2 * 1024)

void initLife();
//int sumNeighborsWithChecks(long oldWorld[N][N], int j, int i);
int sumNeighborsWithChecksTopRow(long oldWorld[N][N], int j, int i);
int sumNeighborsWithChecksBottomRow(long oldWorld[N][N], int j, int i);
int sumNeighborsWithChecksRightCol(long oldWorld[N][N], int j, int i);
int sumNeighborsWithChecksLeftCol(long oldWorld[N][N], int j, int i);
int sumNeighborsNoChecks(long oldWorld[N][N], int j, int i, long cache[3], long otherTwo);
int life(long oldWorld[N][N], long newWorld[N][N]);
int checkHealth(long newCell, long oldCell);
void printWorld(long world[N][N]);

#endif
