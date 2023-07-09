void delete_partition(struct DiskManager *manager, int partition_number)
{
    if (manager->disque_actif == NULL)
    {
        printf("Veuillez sélectionner un disque actif.\n");
        return;
    }
    char command[256];
    sprintf(command, "echo -e \"d\n%d\nw\nq\" | fdisk %s > /dev/null", partition_number, manager->disque_actif->device);
    system(command);
    printf("Partition supprimée avec succès.\n");
}
