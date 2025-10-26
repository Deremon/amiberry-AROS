#include <sys/time.h>
#include <sys/timeb.h>

#include "sysdeps.h"
#include "options.h"


int ftime(struct timeb *tb)
{
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);

    tb->time     = tv.tv_sec;
    tb->millitm  = tv.tv_usec*1000;
    tb->timezone = tz.tz_minuteswest;
    tb->dstflag  = tz.tz_dsttime;

    return 0;
}

void _tzset()
{
}

long _timezone = 0;
int _daylight = 0;
