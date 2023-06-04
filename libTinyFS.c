#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

#include <unistd.h>
#include <string.h>

iNode iNodeList[NUM_INODES_];
DiskInfo DiskList[MAX_NUM_DISKS_];

int tfs_mkfs(char *filename, int nBytes)
{
    return 0;
}

// open disk & do checks

/* tfs_mount(char *filename) “mounts” a TinyFS file system located within ‘filename’. 
 As part of the mount operation, tfs_mount should verify the file system is the correct type. 
 Only one file system may be mounted at a time. 
 Use tfs_unmount to cleanly unmount the currently mounted file system.
  Must return a specified success/error code. */
int tfs_mount(char *filename)
{
    FileSystem currFileSystem; // Change if/when we get a global Filesystem struct
    char blockBuffer[BLOCKSIZE_];

    int i;
    // Check list of file systems that have been opened.
    for(i = 0; i < MAX_NUM_DISKS_; i++){
        if((strcmp(filename, DiskList[i].disk_name) == 0) && 
            DiskList[i].status == 1)
            errorout("File Already Mounted.\n");
    }

    if(readBlock(DiskList[i].fd, SUPER_BLOCK_INDEX_, (void *)blockBuffer) != 0)
        errorout("readBlock failed in tfs_mount.\n");

    memcpy(&(currFileSystem.superblock), blockBuffer, BLOCKSIZE_); // Need to test

    if(currFileSystem.superblock.magic_num == MAGIC_NUM_TYPE_DISK_ || 
       currFileSystem.superblock.magic_num == MAGIC_NUM_TYPE_USB_){
        DiskList[i].status = 1; // Mount the disk
    }
    else{
        errorout("File type not recognized. (Magic Num check in tfs_mount).\n");
    }

    return 0;
}

// close disk
// tfs_unmount(void) “unmounts” the currently mounted file system.
int tfs_unmount(void)
{
    return 0;
}

fileDescriptor tfs_open(char *name)
{

    return 0;
}

int tfs_close(fileDescriptor FD)
{
    return 0;
}

int tfs_write(fileDescriptor FD, char *buffer, int size)
{
    return 0;
}

int tfs_delete(fileDescriptor FD)
{
    return 0;
}

int tfs_readByte(fileDescriptor FD, char *buffer)
{
    return 0;
}

int tfs_seek(fileDescriptor FD, int offset)
{
    return 0;
}

void initDiskInfo(DiskInfo* disk_info, char* disk_name, fileDescriptor fd, size_t disk_size, DiskStatus status)
{
    disk_info = (DiskInfo*) safeMalloc(sizeof(DiskInfo));
    strcpy(disk_info->disk_name, disk_name);
    disk_info->fd = fd;
    disk_info->disk_size = disk_size;
    disk_info->status = status;
}





void printDiskInfo(const DiskInfo* disk_info)
{
    printf("DiskInfo | disk_name: %s | fileDescriptor: %d | disk_size: %zu | status: %d", 
    disk_info->disk_name,
    disk_info->fd,
    disk_info->disk_size,
    disk_info->status);
}