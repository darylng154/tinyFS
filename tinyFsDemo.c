
#include "libDisk.h"
#include "libTinyFS.h"

#include <fcntl.h>

void putBLOCKSIZE(char* block)
{
    int i = 0;
    for(i = 0; i < BLOCKSIZE_; i++)
    {
        block[i] = i;
    }
}

int main(int argc, char *argv[]){

    char* filename = "file1.txt";
    char* block[BLOCKSIZE_ + 1];
    char* write[BLOCKSIZE_ + 1];
    putBLOCKSIZE(write);

    fileDescriptor disk = safeOpen(filename, O_RDWR, S_IRUSR | S_IWUSR);

    readBlock(disk, 0, block);
    printf("block: %s \n", block);

    writeBlock(disk, 5, write);
    printf("write: %s \n", write);

    return 0;
}