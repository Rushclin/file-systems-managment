#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <string.h>

int get_system_info(){
    
    /* 
        Méthode qui doit nous permettre de recuperer les informations sur le système d'expoitation.

        Nous avons par exemple: 
            -   Le système d'exploitation, 
            -   Le nom du disque dur, 
            -   La version du noyau, 
            -   Le modèle de machine, 
            -   Le type de système de fichier. 
    */

    struct utsname sys_info;
    if (uname(&sys_info) != 0) {
        perror("Erreur lors de la récupération des informations sur le système");
        return 0;
    }

    printf("\n====== INFOS DU SYSTEME D'EXPLOITATION =====\n");
    printf("\n");
    printf("Système d'exploitation                      : %s\n", sys_info.sysname);
    printf("Le nom du disque dur est                    : %s\n", sys_info.sysname);
    printf("Version du noyau                            : %s\n", sys_info.release);
    printf("Modèle de machine                           : %s\n", sys_info.machine);
    printf("Type de système de fichiers                 : %s\n", sys_info.sysname);
    printf("\n");
    printf("=============================================\n");
    
    return 1;
}