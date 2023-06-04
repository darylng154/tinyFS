
#include "libDisk.h"
#include "libTinyFS.h"

#include <fcntl.h>

DiskInfo DiskList[MAX_NUM_DISKS_];

void putBLOCKSIZE(char* block)
{
    int i = 0;
    for(i = 0; i < BLOCKSIZE_; i++)
    {
        block[i] = i+1;
    }
}

void init_DiskList()
{
    int i;
    for(i = 0; i < MAX_NUM_DISKS_; i++){
        DiskList[i].diskName[0] = '\0';
        DiskList[i].fd = -1;
        DiskList[i].diskSize = 0;
        DiskList[i].status = CLOSED;
    }
    return;
}

int main(int argc, char *argv[]){

    char* filename = "file2.txt";
    char block[BLOCKSIZE_ + 1];
    char write[BLOCKSIZE_ + 1];
    putBLOCKSIZE(write);
    init_DiskList();

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
    
    printf("\n\n");
    initDiskInfo(disk_info, "Disk Info 1", 0, 0, CLOSED);
    printDiskInfo(disk_info);

    return 0;
}


