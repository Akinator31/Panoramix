/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "panoramix.h"

panoramix_t *init_panoramix_data(panoramix_params_t *params)
{
    panoramix_t *data = malloc(sizeof(panoramix_t));

    if (!data)
        return NULL;
    if (sem_init(&data->wake_up_druid, 0, 0) == -1) {
        free(data);
        return NULL;
    }
    if (sem_init(&data->pot_full, 0, 0) == -1) {
        free(data);
        return NULL;
    }
    if (pthread_mutex_init(&data->pot_access, NULL) == -1) {
        free(data);
        return NULL;
    }
    data->params = params;
    return data;
}


pthread_t **init_villagers_threads(panoramix_params_t *params)
{
    pthread_t **villagers_threads = malloc(sizeof(pthread_t *) *
        (params->nb_villagers + 1));

    for (int i = 0; i < params->nb_villagers; i++) {
        villagers_threads[i] = malloc(sizeof(pthread_t));
        if (!villagers_threads[i]) {
            free(villagers_threads);
            return NULL;
        }
    }

    if (!villagers_threads)
        return NULL;
    villagers_threads[params->nb_villagers] = NULL;
    return villagers_threads;
}
