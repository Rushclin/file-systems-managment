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

    size_t output_length = strlen(output);
    if (output[output_length - 1] == '\n')
        output[output_length - 1] = '\0';

    pclose(fp);

    return output;
}
