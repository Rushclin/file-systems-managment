#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <string.h>

int get_file_info(){
    
    /* 
        Méthode qui doit nous permettre de recuperer les informations sur le système de fichier.

        Nous avons par exemple: 
            -   L'espace totale du disque dur, 
            -   L'espace libre sur le disque dur. 
    */

    struct statvfs fs_info;
    if (statvfs("/", &fs_info) != 0) {
        perror("Erreur lors de la récupération des informations sur le système de fichiers");
        return 0;
    }

    printf("\n======== INFOS DU SYSTEME DE FICHIER =======\n");
    printf("\n");
    printf("Taille totale du système de fichiers        : %lu\n", fs_info.f_blocks * fs_info.f_frsize);
    printf("Taille disponible du système de fichiers    : %lu\n", fs_info.f_bavail * fs_info.f_frsize);
    printf("\n");
    printf("=============================================\n");
    return 1;
}