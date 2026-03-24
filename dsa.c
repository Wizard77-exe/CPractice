#include <stdio.h>

int main() {
    int n; // numbers of elements
    scanf("%d", &n);

    int arr[n]; // array with size n
    
    int isSorted = 1;

    int curr, prev;
    scanf("%d", &prev);
    for (int i = 1; i < n; i++) {
        scanf("%d", &curr);

        if (curr < prev) isSorted = 0;
        prev = curr;
    }

    printf("%s\n", (isSorted?"Yes":"No"));

    return 0;
}