/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdio.h>
#include "panoramix.h"
#include "villagers.h"
#include "druid.h"

panoramix_t *init_panoramix_data(panoramix_params_t *params)
{
    panoramix_t *data = calloc(1, sizeof(panoramix_t));

    if (!data || !params)
        return NULL;
    if (sem_init(&data->wake_up_druid, 0, 0) == -1) {
        free(data);
        return NULL;
    }
    if (sem_init(&data->pot_full, 0, 1) == -1) {
        free(data);
        return NULL;
    }
    if (pthread_mutex_init(&data->pot_access, NULL) != 0) {
        free(data);
        return NULL;
    }
    if (pthread_mutex_init(&data->druid_life_access, NULL) != 0) {
        free(data);
        return NULL;
    }
    if (pthread_mutex_init(&data->druid_is_called_access, NULL) != 0) {
        free(data);
        return NULL;
    }
    data->params = params;
    data->druid_called = 0;
    data->pot = params->pot_size;
    data->villagers_alive = 1;
    data->druid_alive = 1;
    return data;
}

pthread_t **init_villagers_threads(panoramix_t *data)
{
    pthread_t **villagers_threads = malloc(sizeof(pthread_t *) *
        (data->params->nb_villagers + 1));
    villager_t *villager = NULL;

    if (!villagers_threads || !data)
        return NULL;
    for (int i = 0; i < data->params->nb_villagers; i++) {
        villagers_threads[i] = malloc(sizeof(pthread_t));
        villager = create_villager(i, data);
        if (!villager)
            return NULL;
        printf("Villager %d: Going into battle!\n", villager->id);
        if (!villager || !villagers_threads[i] ||
            pthread_create(villagers_threads[i], NULL, villager_work, villager)
            != 0) {
            free(villager);
            free(villagers_threads);
            return NULL;
        }
    }
    villagers_threads[data->params->nb_villagers] = NULL;
    return villagers_threads;
}

pthread_t *init_druid_thread(panoramix_t *data)
{
    pthread_t *druid_thread = malloc(sizeof(pthread_t));
    druid_t *druid = create_druid(data);

    if (!druid_thread || !druid || !data)
        return NULL;
    if (pthread_create(druid_thread, NULL, druid_work, druid) != 0) {
        free(druid);
        free(druid_thread);
        return NULL;
    }
    printf("Druid: I'm ready... but sleepy...\n");
    return druid_thread;
}
