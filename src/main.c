/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "panoramix.h"
#include "semaphore.h"
#include "init.h"
#include "free.h"
#include "villagers.h"
#include "druid.h"

int panoramix(panoramix_t *data)
{
    pthread_t *druid_thread = init_druid_thread(data);
    pthread_t **villagers_threads = init_villagers_threads(data);

    if (!villagers_threads)
        return 84;
    for (int i = 0; i < data->params->nb_villagers; i++) {
        if (pthread_join(*villagers_threads[i], NULL) != 0) {
            return 84;
        }
    }
    data->villagers_alive = 0;
    if (sem_post(&data->wake_up_druid) != 0)
        return 84;
    if (pthread_join(*druid_thread, NULL) != 0) {
        return 84;
    }
    free_villagers_thread(villagers_threads);
    free_druid_thread(druid_thread);
    return 0;
}

int main(int argc, char **argv)
{
    panoramix_params_t *panoramix_params = parse_panoramix(argc, argv);
    panoramix_t *data = init_panoramix_data(panoramix_params);

    if (!data)
        return 84;
    if (panoramix(data) == 84) {
        free_panoramix(data);
        return 84;
    }
    free_panoramix(data);
    return 0;
}
