#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liste_partitions()
{
    system("lsblk -o NAME,SIZE,TYPE,MOUNTPOINT | grep -E '^<device_name>\s|─'");
}
