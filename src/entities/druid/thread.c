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

int refill_pot(druid_t *druid)
{
    int refills_left = druid->nb_refills_left;

    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make %d more refills after this one.\n", refills_left - 1);
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

int set_druid_dead(druid_t *druid)
{
    if (pthread_mutex_lock(&druid->data->druid_life_access) != 0)
        return -1;
    druid->data->druid_alive = 0;
    if (pthread_mutex_unlock(&druid->data->druid_life_access) != 0)
        return -1;
    return 0;
}

void *no_more_ingredients(druid_t *druid)
{
    set_druid_dead(druid);
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    druid->data->druid_called = 0;
    if (sem_post(&druid->data->pot_full) == -1) {
        free(druid);
        return NULL;
    }
    free(druid);
    return NULL;
}

void *druid_work(void *raw_data)
{
    druid_t *druid = (druid_t *)raw_data;
    int refill_pot_result = 0;

    if (sem_wait(&druid->data->wake_up_druid) == -1) {
        free(druid);
        return NULL;
    }
    if (!druid->data->villagers_alive) {
        free(druid);
        return NULL;
    }
    refill_pot_result = refill_pot(druid);
    if (refill_pot_result == 0)
        return no_more_ingredients(druid);
    if (refill_pot_result == -1) {
        free(druid);
        return NULL;
    }
    if (sem_post(&druid->data->pot_full) == -1) {
        free(druid);
        return NULL;
    }
    druid->data->druid_called = 0;
    return druid_work(druid);
}

void free_druid_thread(pthread_t *druid_thread)
{
    free(druid_thread);
}
