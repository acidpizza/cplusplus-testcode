#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

int main()
{
  printf("consumer code\n");
  const int SIZE = 4096;
  const char *name = "OS";
  
  int shm_fd;
  void *ptr;
  int *count = ptr;

  // create the shared memory object
  shm_fd = shm_open(name, O_RDONLY, 0666);
  if (shm_fd == -1)
  {
    shm_unlink(name);
    printf("shared memory failed\n");
    return -1;
  }
  // memory map the share memory object
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  if(ptr == MAP_FAILED)
  {
    printf("Map failed because %s\n", strerror(errno));
    return 1;
  }

  unsigned int old_value = 0;
//  while(1)
  {
    unsigned int value = *((unsigned int*) ptr);
    if(value < old_value) { printf("WE GOT PROBLEM: old = %u, new = %u\n", old_value, value); }
    old_value = value;
    printf("%u\n", value);
    usleep(50000);
  }
  shm_unlink(name);
  return 0;
}
