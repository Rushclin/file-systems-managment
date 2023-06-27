#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_disk_serial_number(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "udevadm info -n %s -q property | grep 'ID_SERIAL_SHORT'", device);

    return execute_command(command);
}