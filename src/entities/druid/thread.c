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
#include "display.h"

int refill_pot(druid_t *druid)
{
    display_cooking(druid);
    if (pthread_mutex_lock(&druid->data->pot_access) != 0)
        return -1;
    druid->data->pot = druid->data->params->pot_size;
    if (pthread_mutex_unlock(&druid->data->pot_access) != 0)
        return -1;
    druid->nb_refills_left -= 1;
    if (druid->nb_refills_left == 0)
        return 0;
    return 1;
}

void *no_more_ingredients(druid_t *druid)
{
    druid->data->druid_alive = 0;
    display_no_more_ingredients(druid);
    druid->data->druid_called = 0;
    for (int i = 0; i < druid->data->villagers_waiting; i++) {
        if (sem_post(&druid->data->pot_full) == -1) {
            free(druid);
            return NULL;
        }
    }
    free(druid);
    return NULL;
}

void *druid_work(void *raw_data)
{
    druid_t *druid = (druid_t *)raw_data;
    int res = 0;

    while (1) {
        if (CHECK(sem_wait(&druid->data->wake_up_druid), free(druid)))
            return NULL;
        if (!druid->data->druid_alive) {
            free(druid);
            return NULL;
        }
        res = refill_pot(druid);
        if (!res)
            return no_more_ingredients(druid);
        if (CHECK(res, free(druid)))
            return NULL;
        if (CHECK(sem_post(&druid->data->pot_full), free(druid)))
            return NULL;
    }
}

void free_druid_thread(pthread_t *druid_thread)
{
    free(druid_thread);
}
