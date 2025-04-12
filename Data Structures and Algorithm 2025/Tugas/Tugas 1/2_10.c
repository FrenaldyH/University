#include <stdio.h>
#include <string.h>

// Shortcut
#define S 1001
#define P(x) printf(x)
#define el printf("%c", '\n')

typedef struct Pel {
    int rank;
    char name[S];
    float max_jump;
} Pel;

void swap(Pel *a, Pel *b) {
    Pel t = *a; *a = *b; *b = t;
}

int partition(Pel arr[], int l, int r) { // Zero indexed
    float pivot = arr[r].max_jump;

    int i, j;
    for(j = i = l; j < r; j++) {
        if(arr[j].max_jump > pivot) {
            swap(&arr[i], &arr[j]); i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

void quicksort(Pel arr[], int l, int r) {
    if(l < r) {
        int mid = partition(arr, l, r);

        quicksort(arr, l, mid - 1);
        quicksort(arr, mid + 1, r);
    }
}

int main() {
    // Declaration
    Pel pelari[8]; 
    char tname[S]; float tjump; int i, j;
    FILE *input = fopen("input210.txt", "r");
    for(i = 0; fscanf(input, "%s %f", tname, &tjump) == 2; i++) {
        // printf("%s %.2f\n", tname, tjump);
        if(i < 8)
            strcpy(pelari[i].name, tname), pelari[i].max_jump = tjump;
        else if(pelari[i % 8].max_jump < tjump) 
            pelari[i % 8].max_jump = tjump;
    }
    quicksort(pelari, 0, 7);

    pelari[0].rank = 1;
    for(i = j = 1; j < 8; j++) {
        if(pelari[j].max_jump != pelari[j - 1].max_jump)
            i = j + 1;
        pelari[j].rank = i;
    }
    
    for(i = 0; i < 8; i++) 
        printf("%d. %s %.2f\n", pelari[i].rank, pelari[i].name, pelari[i].max_jump);

    fclose(input);
    return 0;
}