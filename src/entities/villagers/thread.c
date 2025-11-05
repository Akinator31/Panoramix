/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "panoramix.h"
#include "villagers.h"
#include "display.h"

int is_druid_called(villager_t *villager)
{
    int result = 0;

    if (pthread_mutex_lock(&villager->data->druid_is_called_access) != 0)
        return -1;
    result = villager->data->druid_called;
    if (!result)
        villager->data->druid_called = 1;
    if (pthread_mutex_unlock(&villager->data->druid_is_called_access) != 0)
        return -1;
    return result;
}

int call_druid(villager_t *villager)
{
    if (is_druid_called(villager)) {
        return 1;
    }
    display_pano_wakeup(villager);
    if (sem_post(&villager->data->wake_up_druid) != 0)
        return -1;
    if (sem_wait(&villager->data->pot_full) != 0)
        return -1;
    return 1;
}

int get_pot(villager_t *villager)
{
    int result = 0;

    if (pthread_mutex_lock(&villager->data->pot_access) != 0)
        return -1;
    result = villager->data->pot;
    if (result > 0)
        villager->data->pot -= 1;
    if (pthread_mutex_unlock(&villager->data->pot_access) != 0)
        return -1;
    return result;
}

int get_some_potion(villager_t *villager)
{
    int druid_life = 0;
    int pot_status = get_pot(villager);
    int call_result = 0;

    while (1) {
        pot_status = get_pot(villager);
        if (pot_status > 0) {
            return 1;
        } else {
            druid_life = is_druid_alive(villager);
            if (!druid_life || (druid_life == -1))
                return druid_life;
            call_result = call_druid(villager);
            if (call_result == -1)
                return -1;
        }
    }
}

int is_druid_alive(villager_t *villager)
{
    int result = 0;

    if (pthread_mutex_lock(&villager->data->druid_life_access) != 0)
        return -1;
    result = villager->data->druid_alive;
    if (pthread_mutex_unlock(&villager->data->druid_life_access) != 0)
        return -1;
    return result;
}

void *villager_work(void *raw_data)
{
    villager_t *villager = (villager_t *)raw_data;
    int potion_result = 0;

    display_villager_join(villager);
    while (villager->nb_fights != 0 && is_druid_alive(villager)) {
        display_need_to_drink(villager, get_pot(villager));
        potion_result = get_some_potion(villager);
        if (potion_result == -1) {
            free(villager);
            return NULL;
        }
        if (!potion_result)
            break;
        villager->nb_fights -= 1;
        display_fight(villager);
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
