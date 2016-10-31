#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#include <string.h>
#include <errno.h>

int main() {
  //FILE SIZE
  struct stat *buf = malloc(sizeof(struct stat));
  stat("stat.c",buf);

  printf("File size: %lu bytes\n",buf->st_size);

  //TIME ACCESSED
  time_t timet = buf->st_atime;
  struct tm timetm;
  localtime_r(&timet,&timetm);
  
  char timeStr[80];
  strftime(timeStr, sizeof(timeStr), "%c", &timetm);

  printf("Last accessed: %s\n", timeStr);
}
