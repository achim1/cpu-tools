#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
/* Returns the clock speed of the system’s CPU in MHz, as reported by
/proc/cpuinfo. On a multiprocessor machine, returns the speed of
the first CPU. On error returns zero. */

float get_cpu_temp ()
{
// we are only interested in Tdie for now
FILE* fp;
char buffer[1024];
size_t bytes_read;
char* match = buffer;
/* Read the entire contents of /proc/cpuinfo into the buffer. */
fp = fopen ("/sys/class/hwmon/hwmon0/temp1_input", "r");
bytes_read = fread (buffer, 1, sizeof (buffer), fp);
fclose (fp);
/* Bail if read failed or if buffer isn’t big enough. */

if (bytes_read == 0 || bytes_read == sizeof (buffer)){
  printf("Warning can not read out buffer\n");
  return 0;
}
/* NUL-terminate the text. */
buffer[bytes_read] = '\0';

int cpuTempRaw;
float cpuTemp;
sscanf (match, "%d", &cpuTempRaw);
cpuTemp = (float)cpuTempRaw/1000;  
printf ("CPU temp: %4.0f C\n",cpuTemp);
return cpuTemp;
}

int main ()
{
get_cpu_temp();
return 0;
}


