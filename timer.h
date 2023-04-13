
/****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
****************************************************/


#include <time.h>

/*
	Returns the current time in struct timespec.
*/
struct timespec getTime() {
	struct timespec time;
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
	
	return time;
}


/*
	Returns the elapsed time between two struct timespec. The value
	returned is in seconds.

	@param struct timespec begin 	begin time
	@param struct timespec end 		end time
	
	returns:
		Elapsed time in seconds.
*/
double getElapsed(struct timespec begin, struct timespec end) {
	
	long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    
    return elapsed;
}
