struct Disk
{
    char device[256];
};

struct DiskManager
{
    struct Disk liste_disk[10];
    int nb_disques;
    struct Disk *disque_actif;
};
