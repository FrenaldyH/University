/**
 *      author  : Frenaldy
 *      crreated: 19.04.2025
**/

#include <stdio.h>
#include <stdbool.h>

int target = 36,
input[4][9] = 
{
    {7, 25, 42, 40, 33, 34, 39, 36},
    {92, 22, 91, 24, 89, 20, 35, 36},
    {95, 20, 90, 24, 92, 27, 30, 36},
    {7, 46, 41, 21, 26, 39, 37, 24, 36}
};

int main() {
    bool found_minv, found_maxv, ans;
    int i, j, minv, maxv, idx_false, val_false;

    for(i = 0; i < 4; i++) {
        found_maxv = found_minv = false;
        ans = true;

        printf("Sequence %d:", i + 1);
        for(j = 0; input[i][j] != target; j++)  
            printf(" %d", input[i][j]);
        printf(" %d\n", target);

        for(j = 0; input[i][j] != target; j++) {
            if(found_maxv && input[i][j] > maxv) {
                val_false = input[i][j];
                idx_false = j + 1;
                ans = false;
                break;
            }
            if(found_minv && input[i][j] < minv) {
                val_false = input[i][j];
                idx_false = j + 1;
                ans = false;
                break;
            }

            if(input[i][j] < input[i][j + 1]) {
                found_minv = true;
                minv = input[i][j];
            }
            if(input[i][j] > input[i][j + 1]) {
                found_maxv = true;
                maxv = input[i][j];
            }
        }
        
        printf("Sequence %d ", i + 1);
        if(ans) printf("is valid\n");
        else printf("contains invalid value %d at position %d\n", val_false, idx_false);
    }
    printf("The error occurs because a Binary Search Tree cannot revisit previously excluded value ranges\n");
}