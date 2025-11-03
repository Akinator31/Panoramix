/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

void *villager_work(void *raw_data)
{
    villager_t *villager = (villager_t *)raw_data;

    printf("Villager %d: Going into battle!\n", villager->id);
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
