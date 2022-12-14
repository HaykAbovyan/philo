#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
int main()
{
	struct timeval t;
	struct timeval time;
	gettimeofday(&t, NULL);
	printf("total is %ld\n", t.tv_sec * 1000 + t.tv_usec / 1000);
	
 
}