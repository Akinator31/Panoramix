/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** druid
*/

#include <unistd.h>
#include "panoramix.h"
#include "errors.h"

int is_druid_called(villager_t *villager)
{
    int result = 0;

    if (pthread_mutex_lock(&villager->data->druid_is_called_access) != 0)
        handle_villager_failure(villager);
    result = villager->data->druid_called;
    if (pthread_mutex_unlock(&villager->data->druid_is_called_access) != 0)
        handle_villager_failure(villager);
    return result;
}

int set_druid_called(villager_t *villager)
{
    int allready_on = 0;

    if (pthread_mutex_lock(&villager->data->druid_is_called_access) != 0)
        handle_villager_failure(villager);
    allready_on = villager->data->druid_called;
    villager->data->druid_called = 1;
    if (pthread_mutex_unlock(&villager->data->druid_is_called_access) != 0)
        handle_villager_failure(villager);
    if (allready_on)
        return 0;
    return 1;
}

void set_druid_uncalled(villager_t *villager)
{
    if (pthread_mutex_lock(&villager->data->druid_is_called_access) != 0)
        handle_villager_failure(villager);
    villager->data->druid_called = 0;
    if (pthread_mutex_unlock(&villager->data->druid_is_called_access) != 0)
        handle_villager_failure(villager);
}

int is_druid_alive(villager_t *villager)
{
    int result = 0;

    if (pthread_mutex_lock(&villager->data->druid_life_access) != 0)
        handle_villager_failure(villager);
    result = 1;
    if (pthread_mutex_unlock(&villager->data->druid_life_access) != 0)
        handle_villager_failure(villager);
    return result;
}

int wake_up_druid(villager_t *villager)
{
    if (!is_druid_alive(villager))
        return 0;
    if (is_druid_called(villager)) {
        if (sem_wait(&villager->data->pot_full) != 0)
            handle_villager_failure(villager);
        return 1;
    }
    if (!set_druid_called(villager))
        return wake_up_druid(villager);
    if (sem_post(&villager->data->wake_up_druid) != 0)
        handle_villager_failure(villager);
    if (sem_wait(&villager->data->pot_full) != 0)
        handle_villager_failure(villager);
    set_druid_uncalled(villager);
    return 1;
}
