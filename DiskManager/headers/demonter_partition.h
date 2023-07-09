void demonter_partition(const char *device)
{
    char command[256];
    sprintf(command, "umount %s", device);
    system(command);
    printf("La partition %s a été démontée avec succès.\n", device);
}