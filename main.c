#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH 256

#define MAX_PATH 256

void print_disk_info(const char *device_path) {
    printf("Takam Rushclin");
    char serial_number[MAX_PATH];
    char model[MAX_PATH];

    snprintf(serial_number, MAX_PATH, "%s/serial", device_path);
    snprintf(model, MAX_PATH, "%s/model", device_path);

    FILE *serial_file = fopen(serial_number, "r");
    FILE *model_file = fopen(model, "r");

    if (serial_file && model_file) {
        char serial[MAX_PATH];
        char model_name[MAX_PATH];

        fgets(serial, MAX_PATH, serial_file);
        fgets(model_name, MAX_PATH, model_file);

        printf("Numéro de série du disque dur : %s", serial);
        printf("Modèle du disque dur : %s", model_name);

        fclose(serial_file);
        fclose(model_file);
    }
}

int main(){
    
    struct statvfs fs_info;
    if (statvfs("/", &fs_info) != 0) {
        perror("Erreur lors de la récupération des informations sur le système de fichiers");
        return 1;
    }

    struct utsname sys_info;
    if (uname(&sys_info) != 0) {
        perror("Erreur lors de la récupération des informations sur le système");
        return 1;
    }

    DIR *dir = opendir("/dev");
    if (!dir) {
        perror("Erreur lors de l'ouverture du répertoire /dev");
        return 1;
    }

    // struct dirent *entry;
    // while ((entry = readdir(dir)) != NULL) {
    //     // if (entry->d_type == DT_LNK) {
    //         char serial_number[MAX_PATH];
    //         if (get_disk_serial_number(entry->d_name, serial_number)) {
    //             printf("Disque %s - Numéro de série : %s\n", entry->d_name, serial_number);
    //         } else {
    //             printf("Disque %s - Impossible de récupérer le numéro de série\n", entry->d_name);
    //         }
    //     // }
    // }

    // closedir(dir);

    // Liste des partitions disponible

    FILE *file = fopen("/proc/mounts", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier /proc/mounts");
        return 1;
    }

    // struct statvfs fs_info;
    // struct utsname sys_info;
    if (uname(&sys_info) != 0) {
        perror("Erreur lors de la récupération des informations sur le système");
        fclose(file);
        return 1;
    }

    printf("Liste des partitions disponibles :\n");

    char device[256];
    char mount_point[256];

    // while (fscanf(file, "%255s %255s", device, mount_point) == 2) {
    //     if (statvfs(mount_point, &fs_info) != 0) {
    //         perror("Erreur lors de la récupération des informations sur le système de fichiers");
    //         fclose(file);
    //         return 1;
    //     }

    //     printf("Partition : %s\n", device);
    //     printf("  Point de montage : %s\n", mount_point);
    //     printf("  Taille totale du système de fichiers : %lu\n", fs_info.f_blocks * fs_info.f_frsize);
    //     printf("  Taille disponible du système de fichiers : %lu\n", fs_info.f_bavail * fs_info.f_frsize);
    //     printf("\n");
    // }

    // fclose(file);

// Fin


    printf("Système d'exploitation : %s\n", sys_info.sysname);
    printf("Le nom du disque dur est : %s\n", sys_info.sysname);
    printf("Version du noyau : %s\n", sys_info.release);
    printf("Modèle de machine : %s\n", sys_info.machine);
    printf("Type de système de fichiers : %s\n", sys_info.sysname);
    printf("Taille totale du système de fichiers : %lu\n", fs_info.f_blocks * fs_info.f_frsize);
    printf("Taille disponible du système de fichiers : %lu\n", fs_info.f_bavail * fs_info.f_frsize);


// Obtention des informations supplémentaires sur le disque dur
    print_disk_info("/sys/block/sda");


    return 0;
}