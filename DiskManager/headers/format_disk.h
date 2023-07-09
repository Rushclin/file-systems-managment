void format_disk(struct DiskManager *manager, const char *file_system_type, int partition_size)
{
    if (manager->disque_actif == NULL)
    {
        printf("Veuillez sélectionner un disque actif.\n");
        return;
    }
    char command1[256];
    char command2[256];
    sprintf(command1, "echo -e \"g\nn\np\n\n\n+%dG\nw\nq\" | fdisk %s > /dev/null", partition_size, manager->disque_actif->device);
    if (strcmp(file_system_type, "ext4") == 0)
    {
        sprintf(command2, "mkfs.%s -F %s1 > /dev/null", file_system_type, manager->disque_actif->device);
    }
    else if (strcmp(file_system_type, "ntfs") == 0)
    {
        sprintf(command2, "mkfs.%s -f %s1 > /dev/null", file_system_type, manager->disque_actif->device);
    }
    else
    {
        printf("Type de système de fichiers non pris en charge.\n");
        return;
    }
    system(command1);
    system(command2);
    printf("Disque formaté avec succès.\n");
}