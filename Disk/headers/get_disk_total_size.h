#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long get_disk_total_size(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "lsblk -b -dn -o SIZE %s | awk 'NR==1 {print $1}'", device);

    char* output = execute_command(command);
    if (!output)
        return -1;

    long long total_size = atoll(output);
    free(output);

    return total_size;
}