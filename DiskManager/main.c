#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mount.h>
#include <sys/statvfs.h>

#include "structures/DiskManager.h"

#include "headers/ajout_disk.h"
#include "headers/available_disk.h"
#include "headers/create_partition.h"
#include "headers/delete_partition.h"
#include "headers/demonter_partition.h"
#include "headers/format_disk.h"
#include "headers/lister_disques.h"
#include "headers/monter_partition.h"
#include "headers/retirer_disk.h"
#include "headers/set_active_disk.h"

int main()
{
    struct DiskManager manager;
    manager.nb_disques = 0;
    manager.disque_actif = NULL;

    // Utilisation des fonctions pour gérer les disques

    available_disk();
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