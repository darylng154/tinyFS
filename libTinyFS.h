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
#define MAX_FILE_SIZE_       (DATA_BLKS_PER_INODE_ * BLOCKSIZE_) // File size limit
#define DEFAULT_DISK_NAME_   "tinyFSDisk"

// #define CAL_BY_NUM_BLOCKS_
// Use DISK_SIZE_ where you might use DEFAULT_DISK_SIZE_
#ifdef CAL_BY_NUM_BLOCKS_
#define NUM_BLOCKS_ 100                       // Adjustable 
#define DISK_SIZE_  (BLOCKSIZE_ * NUM_BLOCKS_)
#else
#define NUM_BLOCKS_ (DEFAULT_DISK_SIZE_ / BLOCKSIZE_)
#define DISK_SIZE_   DEFAULT_DISK_SIZE_   
#endif

#define NUM_FREE_BLOCKS_ (NUM_BLOCKS_ - NUM_SPECIAL_BLOCKS_ - NUM_INODES_ - NUM_DATA_BLOCKS_)


typedef int fileDescriptor;
typedef struct disk_info DiskInfo;
typedef struct disk_info FileInfo;
typedef struct superblock Superblock;
typedef struct inode_name_pair iNodeNamePair;
typedef struct inode iNode;

typedef enum {CLOSED, OPEN, MOUNTED, UNMOUNTED} DiskStatus;

struct disk_info{
    char diskName[MAX_DISKNAME_SIZE_];
    fileDescriptor fd;
    size_t diskSize;
    DiskStatus status;
}__attribute__((packed));

struct inode_name_pair{
    char name[MAX_FILENAME_SIZE_];       /* 8 Chars with then a null Terminator*/
    uint8_t inode;      /* 0-255 Inode numbers*/
}__attribute__((packed));

struct inode{
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    /* Since Linux 2.6, the kernel supports nanosecond
        precision for the following timestamp fields.
        For the details before Linux 2.6, see NOTES. */

    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */

    // #define st_atime st_atim.tv_sec      /* Backward compatibility */
    // #define st_mtime st_mtim.tv_sec
    // #define st_ctime st_ctim.tv_sec
}__attribute__((packed));

struct superblock{
    uint8_t magicNum;   // 1st byte of superblock
    iNode specialINode; // special inode that tracks name-inode pairs

    size_t diskSize;
    uint32_t allocBlocks; 
    uint32_t freeBlocks;
    // add data structure of the blocks
}__attribute__((packed));

struct filesystem{
    DiskInfo disk_info;
    Superblock superblock;
    

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

extern DiskInfo DiskList[MAX_NUM_DISKS_];

#endif