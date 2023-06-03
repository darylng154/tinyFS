#ifndef LIBTINYFS_H
#define LIBTINYFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

// max open files = max # inodes + # free blocks

#define BLOCKSIZE_ 256
#define DEFAULT_DISK_SIZE_ 10240 
#define DEFAULT_DISK_NAME_ “tinyFSDisk” 	
typedef int fileDescriptor;

typedef struct disk_info DiskInfo;
typedef struct inode_name_pair iNodeNamePair;
typedef struct inode iNode;
typedef struct superblock Superblock;
typedef struct file_system FileSystem;

typedef enum {CLOSED = 0, OPEN = 1, UNMOUNTED = 0, MOUNTED = 1} Status;

struct disk_info{
    char disk_name[256];
    fileDescriptor fd;
    size_t disk_size;
    Status status; 
}__attribute__((packed));

struct inode_name_pair{
    char name[9];       /* 8 Chars with then a null Terminator*/
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

struct file_system{
    DiskInfo disk_info;
    // opened file resource table
    Superblock superblock;
    iNode special_iNode;
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

void initDiskInfo(DiskInfo* disk_info, char* disk_name, fileDescriptor fd, size_t disk_size, Status status);




void printDiskInfo(const DiskInfo* disk_info);

#endif