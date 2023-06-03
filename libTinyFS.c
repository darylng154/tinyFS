#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

#include <unistd.h>
#include <string.h>

int tfs_mkfs(char *filename, int nBytes)
{
    return 0;
}

// open disk & do checks
int tfs_mount(char *filename)
{
    return 0;
}

// close disk
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

void initDiskInfo(DiskInfo* disk_info, char* disk_name, fileDescriptor fd, size_t disk_size, Status status)
{
    disk_info = (DiskInfo*) safeMalloc(sizeof(DiskInfo));
    strcpy(disk_info->disk_name, disk_name);
    disk_info->fd = fd;
    disk_info->disk_size = disk_size;
    disk_info->status = status;
}





void printDiskInfo(const DiskInfo* disk_info)
{
    printf("DiskInfo | disk_name: %s | fileDescriptor: %d | disk_size: %d | status: %d", 
    disk_info->disk_name,
    disk_info->fd,
    disk_info->disk_size,
    disk_info->status);
}