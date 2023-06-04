#ifndef LIBDISK_H
#define LIBDISK_H

#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

#include <unistd.h>

int openDisk(char *filename, int nBytes);
int readBlock(int disk, int bNum, void *block);
int writeBlock(int disk, int bNum, void *block);
void closeDisk(int disk);
int getDiskListIndex(int disk, char *filename);
int flushDisk(DiskInfo diskInfo);

#endif