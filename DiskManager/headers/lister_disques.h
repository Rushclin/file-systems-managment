void lister_disques(struct DiskManager *manager)
{
    int i;
    if (manager->nb_disques == 0)
    {
        printf("Aucun disque géré par Disk Manager !\n");
    }
    else
    {
        printf("Liste des disques :\n");
        for (i = 0; i < manager->nb_disques; i++)
        {
            printf("%d -- (%s)\n", i + 1, manager->liste_disk[i].device);
        }
    }
}