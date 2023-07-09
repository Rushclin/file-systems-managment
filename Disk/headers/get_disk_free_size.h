#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long get_disk_free_size(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "df --output=avail -B 1 %s | tail -n 1", device);

    char* output = execute_command(command);
    if (!output)
        return -1;

    long long free_size = atoll(output);
    free(output);

    return free_size;
}