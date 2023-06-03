#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

DiskInfo DiskList[MAX_NUM_DISKS_];

int openDisk(char *filename, int nBytes){
  static uint8_t openFiles = 0;
  char blockBuffer[10];
  int flags = 0;
  int modes = 0;
  fileDescriptor fd;

  if(filename == NULL)
    errorout("Filename is NULL.\n");
  
  if(nBytes % BLOCKSIZE_){
    sprintf(blockBuffer, "Number of Bytes is not divisible by BLOCKSIZE (%d)",BLOCKSIZE_);
    errorout(blockBuffer);
  }

  if(nBytes > 0 && access(filename, F_OK) != 0){ /* File does not exist*/
    flags = O_RDWR | O_CREAT;  // Open for read/write, create if it doesnt't exist
    modes = S_IRUSR | S_IWUSR; // Give read write permissions to User
    fd = safeOpen(filename, flags, modes);
  }
  else if(nBytes > 0){ /* File may or may not be created. Open/create for read/write*/
    flags = O_RDWR;   // Open for read/write
    modes = 0;        // Don't need modes when not creating a file
    fd = safeOpen(filename, flags, modes);
  }
  else if(nBytes == 0){ /* Assumed file is open*/
    flags = O_RDONLY; // Open for Read only
    modes = 0;        // Don't need modes when not creating a file
    fd = safeOpen(filename, flags, modes);
  }
  else if(nBytes < 0)
    errorout("Number of bytes must be positive.\n");

    if(openFiles + 1 >= MAX_NUM_DISKS_)
        errorout("To many files open.\n");

    if(filename < MAX_DISKNAME_SIZE_)
      strcpy(DiskList[openFiles].diskName, filename);
    DiskList[openFiles].diskSize = nBytes;
    DiskList[openFiles].fd = fd;
    DiskList[openFiles++].status = 0; //Not mounted

  return fd; /* Souldn't get here*/
}

// bNum = block index
// seek to bNum in disk & read BLOCKSIZE_ bytes
int readBlock(int disk, int bNum, void *block){
    ssize_t count;
    int offset;

    offset = bNum * BLOCKSIZE_;
    lseek(disk, offset, SEEK_SET);
    count = read(disk, block, BLOCKSIZE_);
    if(count > 0)
    {
        return 0; /* 0 on Success*/
    }
    else if(count == -1)
        errorout("#ERROR: readBlock -1.\n");
    else if(count == 0)
        errorout("#ERROR: readBlock EOF - not a valid block number.\n");
    else
        errorout("#ERROR: readBlock failed all cases.\n");

    errorout("#ERROR: readBlock reached this and should not have.\n");
    return -1;
}

int writeBlock(int disk, int bNum, void *block){
  ssize_t count;
  int offset;

  offset = bNum * BLOCKSIZE_;
  lseek(disk, offset, SEEK_SET);
  count = write(disk, block, BLOCKSIZE_);
  if(count > 0)
      return 0; /* 0 on Success*/
  else if(count == -1)
      errorout("#ERROR: writeBlock -1.\n");
  else if(count == 0)
      errorout("#ERROR: writeBlock 0.\n");
  else
      errorout("#ERROR: writeBlock failed all cases.\n");

  errorout("#ERROR: writeBlock reached this and should not have.\n");
  return -1;
}


/* closeDisk() takes a disk number ‘disk’ and makes the disk closed to further I/O; 
i.e. any subsequent reads or writes to a closed disk should return an error. 
Closing a disk should also close the underlying file, 
committing any writes being buffered by the real OS. */

/* Still need to figure out what he means by committing writes. Is there a global
   buffer we need to flush?*/
void closeDisk(int disk){

  errno = 0;
  close(disk);
  
  if(errno)
    errorout("CloseDisk failed.\n");

  return;
}