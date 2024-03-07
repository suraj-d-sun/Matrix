#ifndef __DURATION_H_
#define __DURATION_H_
#include <time.h>
#include <inttypes.h>

typedef struct __duration
{
    uint16_t days;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint64_t nanoseconds;
} duration;

duration get_elapsed_time(struct timespec start_time, struct timespec end_time)
{
    duration d;
    d.days=0;
    d.hours=0;
    d.minutes=0;
    d.seconds=0;
    d.nanoseconds=0;
    long int v;

    long int s1=start_time.tv_sec;
    long int n1=start_time.tv_nsec;

    long int s2=end_time.tv_sec;
    long int n2=end_time.tv_nsec;

    long int diff_sec=0L;
    long int diff_nsec=0L;

    if(n1==n2) diff_sec=s2-s1;
    else if(n2<n1)
    {
        diff_sec=(s2-s1)-1;
        diff_nsec=1000000000L-n1+n2;
    }
    else
    {
        diff_sec=s2-s1;
        diff_nsec=n2-n1;
    }
    d.nanoseconds=diff_nsec;
    v=diff_sec;
    if(v>=60)
    {
        d.seconds=v%60;
        v=v/60;
        if(v>=60)
        {
            d.minutes=v%60;
            v=v/60;
            if(v>=24)
            {
                d.hours=v%24;
                d.days=v/24;
            }
            else
            {
                d.hours=v;
            }
        }
        else
        {
            d.minutes=v;
        }
    }
    else
    {
        d.seconds=v;
    }
    return d;
}
#endif