#include "shop.h"

int read_shop_items (shop_item_t items[ITEMS_SIZE]) {
    FILE *shop_file;
    int count;

    shop_file = fopen ("./resources/data/shop.txt", "r");

    if (shop_file) {
        for (count = 0; count < ITEMS_SIZE; count++) {
            fscanf (shop_file, "%d %d %d %d %d %d", &items[count].price, &items[count].buyed, &items[count].in_use, 
                                                    &items[count].r, &items[count].g, &items[count].b);
        }
        fclose (shop_file);
    } else return READ_SHOP_ERROR;
    return EXIT_SUCCESS;
}

int save_shop_items (shop_item_t items[ITEMS_SIZE]) {
    FILE *shop_file;
    int count;

    shop_file = fopen ("./resources/data/shop.txt", "w");

    if (shop_file) {
        for (count = 0; count < ITEMS_SIZE; count++) 
            fprintf (shop_file, "%d %d %d %d %d %d\n", items[count].price, items[count].buyed, items[count].in_use, 
                                                    items[count].r, items[count].g, items[count].b);
        fclose (shop_file);
    } else return SAVE_SHOP_ERROR;
    return EXIT_SUCCESS;
}