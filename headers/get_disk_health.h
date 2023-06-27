#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
