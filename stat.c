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

  //PERMISSIONS
  printf("Mode: %o\n", buf->st_mode);

  //HUMAN READABLE FORM SIZE
  long B = buf->st_size;
  long KB = B / 1024.0;
  long MB = KB / 1024.0;
  long GB = MB / 1024.0;

  if (KB > 1) {
    if (MB > 1) {
      if (GB > 1) {
	printf("%luGB\n",GB);
      }
      else {
	printf("%luMB\n",MB);
      }
    }
    else {
      printf("%luKB\n",KB);
    }
  }
  else {
    printf("%luB\n",B);
  }

  //HUMAN READABLE PERMISSIONS
  mode_t perms = buf->st_mode;
  char *permStr = calloc(sizeof(char),32);
  if (perms & S_IRUSR) {
    permStr[0] = 'r';
  }
  else {
    permStr[0] = '-';
  }

  if (perms & S_IWUSR) {
    permStr[1] = 'w';
  }
  else {
    permStr[1] = '-';
  }

  if (perms & S_IXUSR) {
    permStr[2] = 'x';
  }
  else {
    permStr[2] = '-';
  }

  if (perms & S_IRGRP) {
    permStr[3] = 'r';
  }
  else {
    permStr[3] = '-';
  }

  if (perms & S_IWGRP) {
    permStr[4] = 'w';
  }
  else {
    permStr[4] = '-';
  }

  if (perms & S_IXGRP) {
    permStr[5] = 'x';
  }
  else {
    permStr[5] = '-';
  }

  if (perms & S_IROTH) {
    permStr[6] = 'r';
  }
  else {
    permStr[6] = '-';
  }

  if (perms & S_IWOTH) {
    permStr[7] = 'w';
  }
  else {
    permStr[7] = '-';
  }

  if (perms & S_IXOTH) {
    permStr[8] = 'x';
  }
  else {
    permStr[8] = '-';
  }

  printf("%s\n",permStr);

  return 0;
}
