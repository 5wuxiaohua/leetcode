#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// https://leetcode.cn/problems/max-area-of-island/
// 岛屿的最大面积
int dfs(int **grid, int gridSize, int* gridColSize, int i, int j) {
    if (i < 0 || i >= gridSize || j < 0 || j >= gridColSize[0] || grid[i][j] == 0) {
        return 0;
    }

    grid[i][j] = 0;
    return 1 + dfs(grid,gridSize, gridColSize, i, j - 1) +
               dfs(grid,gridSize, gridColSize, i, j + 1) + 
               dfs(grid,gridSize, gridColSize, i - 1, j) +
               dfs(grid,gridSize, gridColSize, i + 1, j); 
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize){
    int max = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            int area = 0;
            if (grid[i][j] == 1) {
                area = dfs(grid, gridSize, gridColSize, i, j);
            }

            max = max > area ? max : area;
        }
    }

    return max;
}