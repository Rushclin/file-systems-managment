void retirer_disk(struct DiskManager *manager, const char *serialNumber)
{
    int i;
    for (i = 0; i < manager->nb_disques; i++)
    {
        if (strcmp(manager->liste_disk[i].device, serialNumber) == 0)
        {
            memmove(manager->liste_disk + i, manager->liste_disk + i + 1, (manager->nb_disques - i - 1) * sizeof(struct Disk));
            manager->nb_disques--;
            break;
        }
    }
}