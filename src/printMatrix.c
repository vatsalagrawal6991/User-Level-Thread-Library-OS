//
// Created by baadalvm on 17/08/21.
//
#include <stdio.h>

void printMatrix(int **x, int n){
    int i,j;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%d  ",x[i][j]);
        }
        printf("\n");
    }
}