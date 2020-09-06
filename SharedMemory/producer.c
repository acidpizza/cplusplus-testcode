#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
  printf("producer code\n");
  const int SIZE = 4096;
  const char *name = "OS";
//  const char *message0 = "hello";
//  const char *message1 = "world";
  
  int shm_fd;
  void *ptr;

  // create the shared memory object
  shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
  // configure the size of the shared memory object
  ftruncate(shm_fd, SIZE);
  // memory map the share memory object
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if(ptr==MAP_FAILED)
  {
     printf("Map failed\n");
     return 1;
  }
//  sprintf(ptr, "%s", message0);
//  ptr+= strlen(message0); 
//  sprintf(ptr, "%s", message1);
//  ptr+= strlen(message1);

  unsigned int *count = (unsigned int*) ptr;
  *count = 0;
  while(1)
  {
    //sprintf(ptr, "%d", count);
    (*count)++;
    //printf("%d\n", *((unsigned int*)ptr));
  }

  return 0;
}
