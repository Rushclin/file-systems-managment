#include <stdio.h>
#include <stdlib.h>
#include <libudev.h>

int main() {
    struct udev *udev = udev_new();
    if (!udev) {
        printf("Impossible d'initialiser udev.\n");
        return 1;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;
    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);

        const char *model = udev_device_get_property_value(dev, "ID_MODEL");
        const char *serial = udev_device_get_property_value(dev, "ID_SERIAL_SHORT");
        const char *size = udev_device_get_property_value(dev, "ID_SIZE");

        printf("Modèle : %s\n", model);
        printf("Numéro de série : %s\n", serial);
        printf("Taille : %s\n", size);

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return 0;
}
