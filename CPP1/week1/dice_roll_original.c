// C standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// preprocessor commands
#define SIDES 6
#define R_SIDE (rand() % SIDES + 1)

// monte carlo simulation
int main() {
    int num_trials;
    int j;
    int d1, d2;
    int outcomes[13] = {0};
    srand(clock());
    printf("Enter number of trials: ");
    scanf("%d", &num_trials);
    for (j = 0; j < num_trials; j++) {
        outcomes[ (d1 = R_SIDE) + (d2 = R_SIDE)]++;
    }
    for (j = 2; j < SIDES * 2 + 1; j ++) {
        printf("%d: %lf \n", j, ((double) outcomes[j]) / num_trials );
    }
    return 0;
}
