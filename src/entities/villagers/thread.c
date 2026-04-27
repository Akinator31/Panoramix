/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <unistd.h>
#include "panoramix.h"
#include "villagers.h"
#include "pot.h"
#include "display.h"

int fight(villager_t *villager)
{
    villager->nb_fights--;
    display_fight(villager);
    if (!villager->nb_fights)
        return 0;
    return 1;
}

int drink(villager_t *villager)
{
    int pot = get_pot_from_villager(villager);

    display_need_to_drink(villager, pot);
    if (pot > 0)
        return 1;
    if (!wake_up_druid(villager))
        return 0;
    get_pot_from_villager(villager);
    return 1;
}

void *villager_work(void *raw_data)
{
    villager_t *villager = (villager_t *)raw_data;

    display_villager_join(villager);
    while (1) {
        if (!drink(villager))
            break;
        if (!fight(villager))
            break;
    }
    display_sleep(villager);
    free(villager);
    return NULL;
}

void free_villagers_thread(pthread_t **villagers_threads)
{
    for (int i = 0; villagers_threads[i]; i++) {
        free(villagers_threads[i]);
    }
    free(villagers_threads);
}
