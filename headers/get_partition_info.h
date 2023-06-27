#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_partition_info(const char *device, Partition *partitions, int max_partitions)
{
    char command[256];
    snprintf(command, sizeof(command), "lsblk -n -o NAME,MOUNTPOINT,FSTYPE,PKNAME | grep '^%s'", device);

    FILE *fp = popen(command, "r");
    if (!fp)
    {
        fprintf(stderr, "Erreur lors de l'exécution de la commande\n");
        return 0;
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        if (count >= max_partitions)
        {
            fprintf(stderr, "Nombre maximal de partitions atteint\n");
            break;
        }

        Partition *partition = &partitions[count];
        sscanf(line, "%s %s %s %s", partition->name, partition->mountpoint, partition->fstype, partition->disk);
        count++;
    }

    pclose(fp);
    return count;
}

void print_partitions(const Partition *partitions, int count)
{
    printf("Partitions du disque :\n");
    for (int i = 0; i < count; i++)
    {
        const Partition *partition = &partitions[i];
        printf("Disk: %s, Device: %s, Mountpoint: %s, Filesystem: %s\n", partition->disk, partition->name, partition->mountpoint, partition->fstype);
    }
}
