void create_partition(struct DiskManager *manager, const char *file_system_type, int partition_number, int partition_size)
{
    if (manager->disque_actif == NULL)
    {
        printf("Veuillez sélectionner un disque actif.\n");
        return;
    }
    char command[256];
    sprintf(command, "echo -e \"n\np\n%d\n\n+%dG\nw\nq\" | fdisk %s > /dev/null", partition_number, partition_size, manager->disque_actif->device);
    system(command);
    if (strcmp(file_system_type, "ntfs") == 0)
    {
        sprintf(command, "mkfs.%s -f %s%d > /dev/null", file_system_type, manager->disque_actif->device, partition_number);
    }
    else if (strcmp(file_system_type, "ext4") == 0)
    {
        sprintf(command, "mkfs.%s -F %s%d > /dev/null", file_system_type, manager->disque_actif->device, partition_number);
    }
    else
    {
        printf("Type de système de fichiers non pris en charge.\n");
        return;
    }
    system(command);
    printf("Partition créée avec succès.\n");
}