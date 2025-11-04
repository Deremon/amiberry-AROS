#include "sysdeps.h"
#include "options.h"
#include "memory.h"
#include "newcpu.h"
#include "custom.h"
#include "xwin.h"

int64_t g_uae_epoch = 0;

#ifdef __AROS__ // AROS need the "standard uae" timing method
static volatile frame_time_t last_time, best_time;
static frame_time_t timebase;

static volatile int loops_to_go;
static int rpt_available;

#define TIME_DELAY 200
#define TIME_UNIT  (TIME_DELAY*1000)

#define MAX_FRAME_TIME 9223372036854775807LL
#define uae_msleep(msecs) SDL_Delay (msecs)
#include <signal.h>
#include <setjmp.h>
static jmp_buf catch_test;

static int first_loop = 1;

static RETSIGTYPE illhandler (int foo)
{
    rpt_available = 0;
    longjmp (catch_test, 1);
}

int machdep_inithrtimer (void)
{
    static int done = 0;

    if (!done) {
        rpt_available = 1;

        write_log ("Testing the RDTSC instruction ... ");
        signal (SIGILL, illhandler);
        if (setjmp (catch_test) == 0)
            read_processor_time ();
        signal (SIGILL, SIG_DFL);
        write_log ("done.\n");

        if (! rpt_available) {
            write_log ("Your processor does not support the RDTSC instruction.\n");
            return 0;
        }

        timebase = 0;

        if (timebase <= 0) {

            write_log ("Calibrating TSC frequency...");
            //flush_log ();

            best_time = MAX_FRAME_TIME;
            loops_to_go = 5;

            /* We want exact values... */
            sync (); sync (); sync ();

            int i = loops_to_go;
            frame_time_t bar;

            while (i-- > 0) {
                last_time = read_processor_time ();
                uae_msleep (TIME_DELAY);
                bar = read_processor_time ();
                if (i != loops_to_go && bar - last_time < best_time)
                    best_time = bar - last_time;
            }

            timebase = best_time * (1000000.0 / TIME_UNIT);
        }

        write_log ("TSC frequency: %f MHz\n", timebase / 1000000.0);

        done = 1;
     }
     return done;
}

#endif /* AROS */

void uae_time_calibrate()
{
#ifndef __AROS__
	// Initialize timebase
	g_uae_epoch = read_processor_time();
	syncbase = 1000000; // Microseconds
#else
	// Initialize timebase
	machdep_inithrtimer();
    syncbase = timebase;
#endif
}

#ifdef __AROS__ // AROS time function
int64_t get_aros_time()
{
	uae_s64 foo1, foo2;
    uae_s64 tsc;
    	/* Don't assume the assembler knows rdtsc */
    	__asm__ __volatile__ (".byte 0x0f,0x31" : "=a" (foo1), "=d" (foo2) :);
    	tsc = foo2 << 32 | foo1;
	return (int64_t)tsc;
}
#endif
