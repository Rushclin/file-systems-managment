bool partition_is_mounted(const char *device)
{
    struct statvfs fs;
    if (statvfs(device, &fs) == -1)
    {
        // Erreur lors de la récupération des informations sur le système de fichiers
        return false;
    }

    // Vérifier si le périphérique est monté
    if (fs.f_bsize != 0)
    {
        return true;
    }

    return false;
}

void monter_partition(struct DiskManager *manager, const char *device, const char *mount_point)
{
    if (manager->disque_actif == NULL)
    {
        printf("Veuillez sélectionner un disque actif.\n");
        return;
    }
    char command[256];
    if (partition_is_mounted(device))
    {
        printf("La partition %s est déjà montée.\n", device);
    }
    else
    {
        mkdir(mount_point, 0777);
        sprintf(command, "mount -o rw %s %s", device, mount_point);
        system(command);
        printf("Le disque %s a été monté avec succès au point de montage %s.\n", device, mount_point);
    }
}