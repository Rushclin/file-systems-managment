#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_disk_model(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "lsblk -o MODEL -n -b %s", device);

    return execute_command(command);
}