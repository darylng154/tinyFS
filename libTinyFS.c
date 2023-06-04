#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

#include <unistd.h>
#include <string.h>

// iNode iNodeList[NUM_INODES_];
// Superblock sb;
FileSystem fs;
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

void initFileSystem()
{
    initDiskInfo(&(fs.disk_info));
    initSuperblock(&(fs.superblock));
    initInodeNamePairs(fs.special_inode_list);
    initInodes(fs.inode_blocks);
    initDataBlocks(fs.data_blocks);
    initFreeBlocks(fs.free_blocks);
}

void initSuperblock(Superblock *sb)
{
    sb->magic_num = 0;
    sb->special_bNum = 0; 
    sb->disk_size = 0;
    sb->alloc_blocks = 0;
    sb->free_blocks = 0;
    return;
}

void initInodeNamePairs(iNodeNamePair *pair_list) {
    int i;

    for(i = 0; i < MAX_INDE_NME_PAIRS_; i++){
        strcpy(pair_list[i].name, "");      // Empty string
        pair_list[i].inode = UNUSED_INODE_; // Set to invalid Inode number
    }
    return;
}

void initInodes(iNode *inode_list) {
    int i, j;

    for(i = 0; i < MAX_INDE_NME_PAIRS_; i++){
        inode_list[i].st_dev = 0;
        inode_list[i].st_ino = UNUSED_INODE_;
        for(j = 0; j < NUM_INODES_; j++)
            inode_list[i].data_index[j] = UNUSED_DATA_INDEX_;
        inode_list[i].st_mode = 0;
        inode_list[i].st_nlink = 0;
        inode_list[i].st_uid = 0;
        inode_list[i].st_gid = 0;
        inode_list[i].st_rdev = 0;
        inode_list[i].st_size = 0;
        inode_list[i].st_blksize = 0;
        inode_list[i].st_blocks = 0;
        inode_list[i].st_atim.tv_sec = 0;
        inode_list[i].st_atim.tv_nsec = 0;
        inode_list[i].st_mtim.tv_sec = 0;
        inode_list[i].st_mtim.tv_nsec = 0;
        inode_list[i].st_ctim.tv_sec = 0;
        inode_list[i].st_ctim.tv_nsec = 0;
    }
    return;
}

void initDataBlocks(DataBlock *data_block_list)
{
    int i;
    for(i = 0; i < NUM_DATA_BLOCKS_; i++)
        strcpy(data_block_list[i].data, "");
    
    return;
}

// free_block_list is a char[] in file system. May change to linked list of void*
void initFreeBlocks(char *free_block_list)
{
    strcpy(free_block_list, "");
    return;
}

void initDiskList()
{
    int i;
    for(i = 0; i < MAX_NUM_DISKS_; i++)
        initDiskInfo(&(DiskList[i]));
    
    return;
}

void initDiskInfo(DiskInfo *disk_info)
{
    strcpy(disk_info->disk_name, ""); // Empty string
    disk_info->fd = -1;
    disk_info->disk_size = 0;
    disk_info->status = CLOSED;
    return;
}

void setDiskInfo(DiskInfo* disk_info, char* disk_name, fileDescriptor fd, size_t disk_size, DiskStatus status)
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