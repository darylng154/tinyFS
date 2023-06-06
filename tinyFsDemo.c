
#include "libDisk.h"
#include "libTinyFS.h"

#include <fcntl.h>

DiskInfo DiskList[MAX_NUM_DISKS_];
FileSystem fs;

void putBLOCKSIZE(char* block);

void putBLOCKSIZE(char* block)
{
    int i = 0;
    for(i = 0; i < BLOCKSIZE_; i++)
    {
        block[i] = i+1;
    }
}

int main(int argc, char *argv[]){

    char* filename = "file2.txt";
    char block[BLOCKSIZE_ + 1];
    char write[BLOCKSIZE_ + 1];
    putBLOCKSIZE(write);
    // initDiskList();
    // initFileSystem();

    fileDescriptor disk = openDisk(filename, BLOCKSIZE_);
    // fileDescriptor disk = safeOpen(filename, O_RDWR, S_IRUSR | S_IWUSR);

    writeBlock(disk, 0, write);
    writeBlock(disk, 10, write);
    printf("write: %s \n", write);

    readBlock(disk, 0, block);
    printf("block: %s \n", block);

    readBlock(disk, 5, block);
    printf("block: %s \n", block);

    readBlock(disk, 10, block);
    printf("block: %s \n", block);

    // testing init structs
    DiskInfo* disk_info = NULL;
    
    // printf("\n\n");
    // setDiskInfo(disk_info, "Disk Info 1", 0, 0, CLOSED);
    // printDiskInfo(disk_info);

    printf("TOTAL_BLOCKS_: %d \n", TOTAL_BLOCKS_);

    closeDisk(disk);

    return 0;
}


