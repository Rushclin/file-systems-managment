#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <string.h>

typedef struct {
    char name[256];
    unsigned long long totalSize;
    unsigned long long freeSpace;
    unsigned long long usedSpace;
} DiskInfo;

int getDiskInfo(const char *diskName, DiskInfo *info) {
    struct statvfs df_info;
    
    if (statvfs(diskName, &df_info) == -1) {
        perror("Erreur lors de la récupération des informations sur le disque");
        return -1;
    }
    
    strncpy(info->name, diskName, sizeof(info->name));
    info->totalSize = (unsigned long long)df_info.f_blocks * df_info.f_frsize;
    info->freeSpace = (unsigned long long)df_info.f_bfree * df_info.f_frsize;
    info->usedSpace = info->totalSize - info->freeSpace;
    
    return 0;
}





char* getDiskModel(const char* diskName) {
    char path[256];
    snprintf(path, sizeof(path), "/sys/block/%s/device/model", diskName);

    FILE* modelFile = fopen(path, "r");
    if (!modelFile) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de modèle du disque\n");
        return NULL;
    }

    char model[256];
    if (!fgets(model, sizeof(model), modelFile)) {
        fprintf(stderr, "Erreur lors de la lecture du modèle du disque\n");
        fclose(modelFile);
        return NULL;
    }

    fclose(modelFile);

    // Supprimer les caractères de fin de ligne s'ils existent
    size_t modelLength = strlen(model);
    if (model[modelLength - 1] == '\n')
        model[modelLength - 1] = '\0';

    return strdup(model);
}






int main() {
    const char *diskName = "/";  // Remplacez par le nom du disque souhaité
    DiskInfo diskInfo;
    
    if (getDiskInfo(diskName, &diskInfo) == 0) {
        printf("Informations sur le disque '%s':\n", diskInfo.name);
        printf("Taille totale : %llu bytes\n", diskInfo.totalSize);
        printf("Espace libre : %llu bytes\n", diskInfo.freeSpace);
        printf("Espace utilisé : %llu bytes\n", diskInfo.usedSpace);
    }

     char *model = getDiskModel(diskName);
    
    if (model) {
        printf("Modèle du disque '%s': %s\n", diskName, model);
        free(model);
    }
    
    return 0;
}
