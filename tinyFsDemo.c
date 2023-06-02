
#include "libDisk.h"
#include "libTinyFS.h"

#include <fcntl.h>

int main(int argc, char *argv[]){

    char* filename = "file2.txt";
    char* block[BLOCKSIZE_ + 1];
    char* write[BLOCKSIZE_ + 1];

    fileDescriptor disk = openDisk(filename, 100);
    // fileDescriptor disk = safeOpen(filename, O_RDWR, S_IRUSR | S_IWUSR);

    // readBlock(disk, 0, block);
    // printf("block: %s \n", block);

    // readBlock(disk, 5, block);
    // printf("block: %s \n", block);

    // readBlock(disk, 8, block);
    // printf("block: %s \n", block);

    writeBlock(disk, 0, write);
    writeBlock(disk, 8, write);
    printf("write: %s \n", write);

    return 0;
}