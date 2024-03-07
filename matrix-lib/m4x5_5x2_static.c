#include <stdio.h>
#include <stdlib.h>
#include "duration.h"
#define A_ROWS 4
#define A_COLS 5
#define B_ROWS A_COLS
#define B_COLS 2
#define C_ROWS A_ROWS
#define C_COLS B_COLS


int main()
{
    duration time_taken;
    struct timespec start_time, end_time;
    int x[A_ROWS][A_COLS] = {{1, 2, 3, 4, 5},
                             {6, 7, 8, 9, 10},
                             {11, 12, 13, 14, 15},
                             {16, 17, 18, 19, 20}};

    int y[B_ROWS][B_COLS] = {{10, 20},
                             {30, 40},
                             {50, 60},
                             {70, 80},
                             {90, 100}};

    int z[C_ROWS][C_COLS];
    int r1, r2, r3, c1, c2, c3, value;
    int r,c;
    system("date");
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for(r1=0;r1<A_ROWS;++r1)
    {
        for(c2=0;c2<B_COLS;++c2)
        {
            value=0;
            for(r2=0,c1=0;c1<A_COLS;++c1,++r2)
            {
                value+=(x[r1][c1])*(y[r2][c2]);
            }
            r3=r1;
            c3=c2;
            z[r3][c3]=value;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_taken = get_elapsed_time(start_time, end_time);
    printf("%u days, %u hours, %u minutes, %u seconds, %lu nano_sec\n", time_taken.days, time_taken.hours, time_taken.minutes, time_taken.seconds, time_taken.nanoseconds);
    system("date");
    for(r3=0;r3<C_ROWS;++r3)
    {
        for(c3=0;c3<C_COLS;++c3)
        {
            printf("%8d",z[r3][c3]);
        }
        printf("\n");
    }
    return 0;
}
