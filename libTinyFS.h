#ifndef LIBTINYFS_H
#define LIBTINYFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_NUM_DISKS_       10       // How many disks can be opened at a time
#define BLOCKSIZE_           256      // Read/Write block sizes
#define DEFAULT_DISK_SIZE_   10240    // Size of disk. Must be multiple of BLOCKSIZE_. 
#define TOTAL_BLOCKS_       (DEFAULT_DISK_SIZE_/BLOCKSIZE_)
#define MAX_FILENAME_SIZE_       9      // support names up to 8 alphanumeric characters
#define MAX_DISKNAME_SIZE_      256
#define MAX_NUM_DISKS_          1
#define MAX_INDE_NME_PAIRS_ ((uint8_t)(BLOCKSIZE_ / sizeof(iNodeNamePair))) // Assuming Special Inode is 1 block


#define SUPER_BLOCK_INDEX_   0          // Block location on disk for readBlock
#define MAGIC_NUM_INDEX_     0          // Block location on disk for readBlock
#define MAGIC_NUM_TYPE_DISK_ 0x5A       // tinyFS magic number


typedef int fileDescriptor;
typedef struct disk_info DiskInfo;
typedef struct disk_info FileInfo;
typedef struct superblock Superblock;
typedef struct inode_name_pair iNodeNamePair;
typedef struct inode iNode;
typedef struct data_block DataBlock;
typedef struct superblock Superblock;
typedef struct file_system FileSystem;

typedef enum {CLOSED, OPEN, MOUNTED, UNMOUNTED} DiskStatus;

struct disk_info
{
    char disk_name[MAX_DISKNAME_SIZE_];
    fileDescriptor fd;
    size_t disk_size;
    DiskStatus status;
}__attribute__((packed));

struct inode_name_pair
{
    char name[MAX_FILENAME_SIZE_]; /* 8 Chars with then a null Terminator*/
    uint8_t inode;                 /* 0-255 Inode numbers*/
}__attribute__((packed));

struct inode
{
    dev_t     st_dev;               /* ID of device containing file. 8 Bytes*/
    ino_t     st_ino;               /* Inode number. 40 Bytes*/
    // uint8_t   data_index[DATA_BLKS_PER_INODE_]; /* Indexs of data blocks. 5 Bytes(adjustable) */
    mode_t    st_mode;              /* File type and mode. 4 Bytes*/
    nlink_t   st_nlink;             /* Optional. Number of hard links. 8 Bytes*/
    uid_t     st_uid;               /* User ID of owner. 4 Bytes*/
    gid_t     st_gid;               /* Group ID of owner. 4 Bytes*/
    dev_t     st_rdev;              /* Device ID (if special file). 8 Bytes*/
    off_t     st_size;              /* Total size, in bytes. 8 Bytes*/
    blksize_t st_blksize;           /* Block size for filesystem I/O. 8 Bytes*/
    blkcnt_t  st_blocks;            /* Number of 512B blocks allocated. 8 Bytes*/

    struct timespec st_atim;        /* Time of last access. 16 Bytes*/
    struct timespec st_mtim;        /* Time of last modification. 16 Bytes*/
    struct timespec st_ctim;        /* Time of last status change. 16 Bytes*/
}__attribute__((packed));

struct superblock
{
    uint8_t magic_num;   // 1st byte of superblock
    // special inode block number of inode that tracks name-inode pairs
    // You will also need to create one special inode that represents the root directory. 
    // You can think of this as a special file whose data contains name-inode pairs for all 
    // the files within TinyFS. You must support names up to 8 alphanumeric characters (not 
    // including a NULL terminator), and no longer. For example: “file1234”, “file1” or “f”.
    int special_bNum; 

    uint32_t max_blocks;
    uint32_t inode_blocks;
    uint8_t data_blocks;
    // uint32_t alloc_blocks;
    uint32_t free_blocks;
    // add data structure of the blocks (potentiall managing all block types)
}__attribute__((packed));

struct data_block
{
    char data[BLOCKSIZE_];
}__attribute__((packed));

struct file_system
{
    // DiskInfo disk_info;  // moved file system inside of DiskInfo
    // opened file resource table
    Superblock superblock;
    // iNodeNamePair special_inode_list[MAX_INDE_NME_PAIRS_];
    // iNode inode_blocks[NUM_INODES_];
    // DataBlock data_blocks[NUM_DATA_BLOCKS_];
    // char free_blocks[NUM_FREE_BLOCKS_]; // Might consider changing to linked list
}__attribute__((packed));

int tfs_mkfs(char *filename, int nBytes);
int tfs_mount(char *filename);
int tfs_unmount(void);
fileDescriptor tfs_open(char *name);
int tfs_close(fileDescriptor FD);
int tfs_write(fileDescriptor FD, char *buffer, int size);
int tfs_delete(fileDescriptor FD);
int tfs_readByte(fileDescriptor FD, char *buffer);
int tfs_seek(fileDescriptor FD, int offset);

void initFileSystem();
void initSuperblock(Superblock *sb);
void initInodeNamePairs(iNodeNamePair *pair_list);
void initInodes(iNode *inode_list);
void initDataBlocks(DataBlock *data_block_list);
void initFreeBlocks(char *free_block_list);
void initDiskList();
void initDiskInfo(DiskInfo *disk_info);
void setDiskInfo(DiskInfo* disk_info, char* disk_name, fileDescriptor fd, size_t disk_size, DiskStatus status);
void printDiskInfo(const DiskInfo* disk_info);

// extern DiskInfo DiskList[MAX_NUM_DISKS_];
// extern iNode iNodeList[NUM_INODES_];
// extern Superblock sb;
// extern FileSystem fs; 
extern DiskInfo currDisk;

#endif