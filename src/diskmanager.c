#include "diskmanager.h"

void listUUID(void){

    blkid_cache cache;
    blkid_dev_iterate iter;
    blkid_dev dev;
    const char *uuid, *devname;

    // Charger le cache de blkid
    if (blkid_get_cache(&cache, NULL) != 0) {
        fprintf(stderr, "Erreur lors de la création du cache blkid\n");

    }

    // Créer un itérateur pour parcourir les périphériques disponibles
    iter = blkid_dev_iterate_begin(cache);
    if (!iter) {
        fprintf(stderr, "Erreur lors de la création de l'itérateur blkid\n");
        blkid_put_cache(cache);

    }

    // Parcourir tous les périphériques
    while (blkid_dev_next(iter, &dev) == 0) {
    
        // Obtenir le nom du périphérique (ex : /dev/sda1)
        devname = blkid_dev_devname(dev);

        // Récupérer l'UUID du périphérique
        uuid = blkid_get_tag_value(cache, "UUID", devname);
        if (uuid) {
            printf("Périphérique : %s, UUID : %s\n", devname, uuid);
        } else {
            printf("Périphérique : %s n'a pas d'UUID.\n", devname);
        }
    }

    // Libérer l'itérateur et le cache
    blkid_dev_iterate_end(iter);
    blkid_put_cache(cache);

}
int getDiskSize(char *devName){
	
	int diskSize = 0;
	
	//Reading the file in /sys/block/sdx/size
	FILE *sizeFile = NULL;
	
	char sizeFilePath[20];
	strcpy(sizeFilePath, "/sys/block/");
	strcat(sizeFilePath, devName);
	strcat(sizeFilePath, "/size");
	
	sizeFile = fopen(sizeFilePath, "r");
	fscanf(sizeFile, "%d", &diskSize);  
	
	return diskSize;
}
