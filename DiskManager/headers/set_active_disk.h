void set_active_disk(struct DiskManager *manager, const char *serialNumber)
{
    int i;
    for (i = 0; i < manager->nb_disques; i++)
    {
        if (strcmp(manager->liste_disk[i].device, serialNumber) == 0)
        {
            manager->disque_actif = &manager->liste_disk[i];
            printf("Le disque (%s) a été défini comme disque actif.\n", manager->disque_actif->device);
            return;
        }
    }
    printf("Le disque (%s) n'a pas été trouvé.\n", serialNumber);
}