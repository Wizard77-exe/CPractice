#include <stdio.h>
#include "myLibs/colors/colors.h"

/*#define MAX 100

void printSpiral(int mat[MAX][MAX], int n, int m) {
    int top = 0, bottom = n - 1;
    int left = 0, right = m - 1;

    while (top <= bottom && left <= right) {

        // left -> right
        for (int j = left; j <= right; j++) {
            printf("%d ", mat[top][j]);
        }
        top++;

        // top -> bottom
        for (int i = top; i <= bottom; i++) {
            printf("%d ", mat[i][right]);
        }
        right--;

        // right -> left
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                printf("%d ", mat[bottom][j]);
            }
            bottom--;
        }

        // bottom -> top
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                printf("%d ", mat[i][left]);
            }
            left++;
        }
    }
}*/

int main() {

    // Spiral matrix
    //int n, m;
    /*int mat[MAX][MAX];

    printf("Enter rows and cols: ");
    scanf("%d %d", &n, &m);

    printf("Enter matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("Spiral order:\n");
    printSpiral(mat, n, m);*/

    // check alternating bits
    /*int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int x = n ^ (n >> 1);
    if ((x & (x + 1)) == 0) {
        printf("The number %d has an alternating bits pattern", n);
    }*/

    cprint(RED, BLKB, "Hello, World");

    return 0;
}