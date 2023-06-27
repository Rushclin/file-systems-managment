#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTITIONS 10
#define MAX_NAME_LENGTH 128
#define MAX_MOUNTPOINT_LENGTH 128
#define MAX_FSTYPE_LENGTH 128
#define MAX_DISK_LENGTH 128

typedef struct {
    char name[MAX_NAME_LENGTH];
    char mountpoint[MAX_MOUNTPOINT_LENGTH];
    char fstype[MAX_FSTYPE_LENGTH];
    char disk[MAX_DISK_LENGTH];
} Partition;
