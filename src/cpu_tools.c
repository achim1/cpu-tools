#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

#include "cpu_tools.h"

/* Returns the clock speed of the system’s CPU in MHz, as reported by
/proc/cpuinfo. On a multiprocessor machine, returns the speed of
the first CPU. On error returns zero. */

float get_cpu_clock_speed (){
    // get the number of cores    
    int ncpu = get_nprocs_conf();
    printf("We found %d cores\n", ncpu);
    
    FILE* fp;
    int nmhz = 0;
    int offset = 0;
    int cpuCount = 0;
    char buffer[100*1024];
    size_t bytes_read;
    char* match = buffer;
    float clock_speed[64]; // support up to 64 cores
    float single_core_speed = 0;

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

    while (ncpu)
    {
      /* Parse the line to extract the clock speed. */
      match = strstr (match, "cpu MHz");
    
      nmhz = sscanf (match, "cpu MHz : %f", &single_core_speed);
      printf ("CPU %d clock speed: %4.0f MHz\n",cpuCount, single_core_speed);
      clock_speed[cpuCount] = single_core_speed;
      ncpu -= 1;
      cpuCount += 1;    
      // walk through the buffer
      match +=100;
}
return *clock_speed;
}

/***************************************************/

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
    
void test()
{
    printf ("Greetings Earthlings!\n");

}

