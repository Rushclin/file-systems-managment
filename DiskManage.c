#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Les structures pour la manipulation du Disque Dur
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

void availableDisk()
{
    system("lsblk -o NAME,SIZE,TYPE,MOUNTPOINT | grep -E '^<device_name>\s|─'");
}

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

void monter_partition(struct DiskManager *manager, const char *device, const char *mount_point)
{
    if (manager->disque_actif == NULL)
    {
        printf("Veuillez sélectionner un disque actif.\n");
        return;
    }
    char command[256];
    if (manager->disque_actif->partition_is_mounted(device))
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

void demonter_partition(const char *device)
{
    char command[256];
    sprintf(command, "umount %s", device);
    system(command);
    printf("La partition %s a été démontée avec succès.\n", device);
}

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

int main()
{
    struct DiskManager manager;
    manager.nb_disques = 0;
    manager.disque_actif = NULL;

    // Utilisation des fonctions pour gérer les disques
    availableDisk();
    lister_disques(&manager);
    ajout_disk(&manager, "/dev/sda");
    // retirer_disk(&manager, "/dev/sda");
    // set_active_disk(&manager, "/dev/sdb");
    // format_disk(&manager, "ext4", 10);
    // monter_partition(&manager, "/dev/sdb1", "/mnt");
    // demonter_partition("/dev/sdb1");
    // delete_partition(&manager, 1);
    // create_partition(&manager, "ext4", 2, 20);
    return 0;
}