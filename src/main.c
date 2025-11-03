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

void *print_via_thread(void *raw_data)
{
    pthread_t thread = pthread_self();
    panoramix_t *data = (panoramix_t *)raw_data;

    printf("Hey, here is my thread number : %lu. Data pointer : %p\n", thread, data);
}

int panoramix(panoramix_params_t *params)
{
    panoramix_t *data = init_panoramix_data(params);
    pthread_t **villagers_threads = init_villagers_threads(params);

    for (int i = 0; i < params->nb_villagers; i++) {
        if (pthread_create(&villagers_threads[i], NULL, print_via_thread, data) != 0) {
            free(data);
            return 84;
        }
    }

    for (int i = 0; i < params->nb_villagers; i++) {
        pthread_join(*villagers_threads[i], NULL);
    }

    if (!data)
        return 84;
    free(data);
    free(villagers_threads);
}

int main(int argc, char **argv)
{
    panoramix_params_t *panoramix_params = parse_panoramix(argc, argv);

    if (!panoramix_params)
        return 84;
    panoramix(panoramix_params);
    free(panoramix_params);
    return 0;
}
