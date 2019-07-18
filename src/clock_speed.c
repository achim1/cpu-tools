#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
/* Returns the clock speed of the system’s CPU in MHz, as reported by
/proc/cpuinfo. On a multiprocessor machine, returns the speed of
the first CPU. On error returns zero. */

float get_cpu_clock_speed ()
{

int ncpu = get_nprocs_conf();
printf("We found %d cores\n", ncpu);

FILE* fp;
char buffer[100*1024];
size_t bytes_read;
char* match = buffer;
float clock_speed;
/* Read the entire contents of /proc/cpuinfo into the buffer. */
fp = fopen ("/proc/cpuinfo", "r");
bytes_read = fread (buffer, 1, sizeof (buffer), fp);
fclose (fp);
/* Bail if read failed or if buffer isn’t big enough. */

if (bytes_read == 0 || bytes_read == sizeof (buffer)){
  printf("Warning can not read out buffer\n");
  return 0;
}
/* NUL-terminate the text. */
buffer[bytes_read] = '\0';

if (match == NULL)
{
printf("Can not find cpu freq");
return 0;
}
int nmhz;
int offset = 0;
int cpuCount = 0;
while (ncpu)
{
  /* Parse the line to extract the clock speed. */
  match = strstr (match, "cpu MHz");

  nmhz = sscanf (match, "cpu MHz : %f", &clock_speed);
  printf ("CPU %d clock speed: %4.0f MHz\n",cpuCount, clock_speed);
  ncpu -= 1;
  cpuCount += 1;

  // walk through the buffer
  match +=100;
}
return clock_speed;
}
int main ()
{
get_cpu_clock_speed();
//printf ("CPU clock speed: %4.0f MHz\n", get_cpu_clock_speed ());
return 0;
}


