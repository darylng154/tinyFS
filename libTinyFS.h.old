#ifndef LIBTINYFS_H
#define LIBTINYFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

// Fixed. Don't change
#define MAX_DISKNAME_SIZE_   256      // OS limits filename size
#define MAX_FILENAME_SIZE_   9        // P4 limits filename size
#define SUPER_BLOCK_INDEX_   0        // Block location on disk for readBlock
#define MAGIC_NUM_INDEX_     0        // Block location on disk for readBlock
#define MAGIC_NUM_TYPE_DISK_ 7        // Block location on disk for readBlock
#define MAGIC_NUM_TYPE_USB_  9        // Block location on disk for readBlock

// Ajustable for testing
#define MAX_NUM_DISKS_       10       // How many disks can be opened at a time
#define BLOCKSIZE_           256      // Read/Write block sizes
// MAKE SURE NUM_FILES_ * NUM_FILES_ < (NUM_BLOCKS_ - NUM_SPECIAL_BLOCKS_)
#define NUM_FILES_           5        // Total number of files that can exist on disk
#define DATA_BLKS_PER_INODE_ 5        // Max number of data blocks per inode
#define DEFAULT_DISK_SIZE_   10240    // Size of disk. Must be multiple of BLOCKSIZE_. 

// Fixed. Don't change
#define NUM_SPECIAL_BLOCKS_  2                                   // Superblock & Special Inode
#define NUM_INODES_          NUM_FILES_
#define NUM_DATA_BLOCKS_    (DATA_BLKS_PER_INODE_ * NUM_INODES_) // Max number of data blocks
#define MAX_FILE_SIZE_      (DATA_BLKS_PER_INODE_ * BLOCKSIZE_)  // File size limit
#define SIZE_INDE_NAME_PAIR_ 10
#define MAX_INDE_NME_PAIRS_ ((uint8_t)(BLOCKSIZE_ / SIZE_INDE_NAME_PAIR_)) // Assuming Special Inode is 1 block
#define INVALID_INODE_      (BLOCKSIZE_ - 1)  // Inode-name pair's limit number of inodes to 1/10th of blocksize
#define UNUSED_INODE_        INVALID_INODE_   // Invalid Inode works as a unused inode flag.
#define INVALID_DATA_INDEX_  (BLOCKSIZE_ - 1) // Data blocks will be < blocksize
#define UNUSED_DATA_INDEX_   INVALID_DATA_INDEX_ // Invalid data index works as a unused data block.
#define DEFAULT_DISK_NAME_   "tinyFSDisk"

// #define CAL_BY_NUM_BLOCKS_
// Use DISK_SIZE_ where you might use DEFAULT_DISK_SIZE_
#ifdef CAL_BY_NUM_BLOCKS_
#define NUM_BLOCKS_ 100                       // Adjustable 
#define DISK_SIZE_  (BLOCKSIZE_ * NUM_BLOCKS_)
#else
#define NUM_BLOCKS_ (DEFAULT_DISK_SIZE_ / BLOCKSIZE_)
#define DISK_SIZE_   DEFAULT_DISK_SIZE_   
#endif // CAL_BY_NUM_BLOCKS_

#define NUM_FREE_BLOCKS_ (NUM_BLOCKS_ - NUM_SPECIAL_BLOCKS_ - NUM_INODES_ - NUM_DATA_BLOCKS_)

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
    uint8_t   data_index[DATA_BLKS_PER_INODE_]; /* Indexs of data blocks. 5 Bytes(adjustable) */
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

    size_t disk_size;
    uint32_t alloc_blocks;
    uint32_t free_blocks;
    // add data structure of the blocks (potentiall managing all block types)
}__attribute__((packed));

struct data_block
{
    char data[BLOCKSIZE_];
}__attribute__((packed));

struct file_system
{
    DiskInfo disk_info;
    // opened file resource table
    Superblock superblock;
    iNodeNamePair special_inode_list[MAX_INDE_NME_PAIRS_];
    iNode inode_blocks[NUM_INODES_];
    DataBlock data_blocks[NUM_DATA_BLOCKS_];
    char free_blocks[NUM_FREE_BLOCKS_]; // Might consider changing to linked list
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

extern DiskInfo DiskList[MAX_NUM_DISKS_];
// extern iNode iNodeList[NUM_INODES_];
// extern Superblock sb;
extern FileSystem fs; 

#endif