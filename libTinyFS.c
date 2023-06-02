#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"
#include <unistd.h>

int tfs_mkfs(char *filename, int nBytes)
{
    return 0;
}

int tfs_mount(char *filename)
{
    return 0;
}


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