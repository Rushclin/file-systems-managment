#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_OUTPUT_SIZE 1024

char* execute_command(const char* command) {
    FILE* fp = popen(command, "r");
    if (!fp) {
        fprintf(stderr, "Erreur lors de l'exécution de la commande\n");
        return NULL;
    }

    char* output = malloc(COMMAND_OUTPUT_SIZE);
    if (!output) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour la sortie de la commande\n");
        pclose(fp);
        return NULL;
    }

    if (!fgets(output, COMMAND_OUTPUT_SIZE, fp)) {
        fprintf(stderr, "Erreur lors de la lecture de la sortie de la commande\n");
        free(output);
        pclose(fp);
        return NULL;
    }

    // Supprimer les caractères de fin de ligne s'ils existent
    size_t output_length = strlen(output);
    if (output[output_length - 1] == '\n')
        output[output_length - 1] = '\0';

    pclose(fp);

    return output;
}

char* get_disk_model(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "lsblk -o MODEL -n -b %s", device);

    return execute_command(command);
}

char* get_disk_serial_number(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "udevadm info -n %s -q property | grep 'ID_SERIAL_SHORT'", device);

    return execute_command(command);
}

long long get_disk_total_size(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "lsblk -b -dn -o SIZE %s | awk 'NR==1 {print $1}'", device);

    char* output = execute_command(command);
    if (!output)
        return -1;

    long long total_size = atoll(output);
    free(output);

    return total_size;
}

long long get_disk_free_size(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "df --output=avail -B 1 %s | tail -n 1", device);

    char* output = execute_command(command);
    if (!output)
        return -1;

    long long free_size = atoll(output);
    free(output);

    return free_size;
}

// void print_partition_info(const char* device) {
//     char command[256];
//     snprintf(command, sizeof(command), "lsblk -n -o NAME,MOUNTPOINT,FSTYPE | grep '^%s'", device);

//     FILE* fp = popen(command, "r");
//     if (!fp) {
//         fprintf(stderr, "Erreur lors de l'exécution de la commande\n");
//         return;
//     }

//     printf("Partitions du disque %s :\n", device);
//     char line[256];
//     while (fgets(line, sizeof(line), fp)) {
//         char name[128], mountpoint[128], fstype[128];
//         sscanf(line, "%s %s %s", name, mountpoint, fstype);
//         printf("Device: %s, Mountpoint: %s, Filesystem: %s\n", name, mountpoint, fstype);
//     }

//     pclose(fp);
// }

void print_partition_info(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "lsblk -n -o NAME,MOUNTPOINT,FSTYPE,PKNAME | grep '^%s'", device);

    FILE* fp = popen(command, "r");
    if (!fp) {
        fprintf(stderr, "Erreur lors de l'exécution de la commande\n");
        return;
    }

    printf("%s", command);

    printf("Partitions du disque %s :\n", device);
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char name[128], mountpoint[128], fstype[128], parent[128];
        sscanf(line, "%s %s %s %s", name, mountpoint, fstype, parent);
        printf("Disk: %s, Device: %s, Mountpoint: %s, Filesystem: %s\n", parent, name, mountpoint, fstype);
    }

    pclose(fp);
}


char* get_disk_health(const char* device) {
    char command[256];
    snprintf(command, sizeof(command), "df --output=pcent %s | tail -n 1", device);

    char* output = execute_command(command);
    if (!output)
        return "Erreur lors de la récupération de l'état de santé du disque";

    int usage_percent = atoi(output);
    free(output);

    if (usage_percent >= 90)
        return "Critique";
    else if (usage_percent >= 70)
        return "Élevé";
    else if (usage_percent >= 50)
        return "Moyen";
    else
        return "Bon";
}

int main() {
    const char* device = "/dev/sda";

    char* model = get_disk_model(device);
    if (model) {
        printf("Modèle du disque %s : %s\n", device, model);
        free(model);
    }

    char* serial_number = get_disk_serial_number(device);
    if (serial_number) {
        printf("Numéro de série du disque %s : %s\n", device, serial_number);
        free(serial_number);
    }

    long long total_size = get_disk_total_size(device);
    if (total_size >= 0)
        printf("Taille totale du disque %s : %lld octets\n", device, total_size);
    else
        printf("Impossible d'obtenir la taille totale du disque %s\n", device);

    long long free_size = get_disk_free_size(device);
    if (free_size >= 0)
        printf("Taille libre du disque %s : %lld octets\n", device, free_size);
    else
        printf("Impossible d'obtenir la taille libre du disque %s\n", device);

    print_partition_info(device);

    const char* health = get_disk_health(device);
    printf("État de santé du disque %s : %s\n", device, health);

    return 0;
}
