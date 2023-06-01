
#include "libDisk.h"
#include "libTinyFS.h"


int main(int argc, char *argv[]){

    char* filename = "file2.txt";
    char* block[BLOCKSIZE_ + 1];

    fileDescriptor disk = safeOpen(filename);

    readBlock(disk, 0, block);

    printf("block: %s \n", block);

    return 0;
}