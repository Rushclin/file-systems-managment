#include <stdio.h>
#include <stdlib.h>

#include "headers/execute_command.h"
#include "headers/get_disk_free_size.h"
#include "headers/get_disk_health.h"
#include "headers/get_disk_model.h"
#include "headers/get_disk_serial_number.h"
#include "headers/get_disk_total_size.h"
#include "headers/get_partition_info.h"

#define MAX_PATH 256

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    printf("Specifiez le nom du disque : %s \n", argv[0]);
    exit(0);
  }

  char device[MAX_PATH];
  snprintf(device, MAX_PATH, "%s", argv[1]);

  printf("Le chemin de disque est : %s\n", device);

  char *model = get_disk_model(device);
  if (model)
  {
    printf("Modèle du disque %s : %s\n", device, model);
    free(model);
  }

  char *serial_number = get_disk_serial_number(device);
  if (serial_number)
  {
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

  // Lister les partitions sur le disque
  liste_partitions();

  return 0;
}