void ajout_disk(struct DiskManager *manager, const char *disk_device)
{
    if (manager->nb_disques >= 10)
    {
        printf("Nombre maximum de disques atteint.\n");
        return;
    }
    struct Disk new_disk;
    strcpy(new_disk.device, disk_device);
    manager->liste_disk[manager->nb_disques++] = new_disk;
}