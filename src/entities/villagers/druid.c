/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** druid
*/

#include <unistd.h>
#include "panoramix.h"
#include "errors.h"
#include "display.h"

int is_druid_alive(villager_t *villager)
{
    return villager->data->druid_alive;
}

int call_druid(villager_t *villager)
{
    if (pthread_mutex_lock(&villager->data->pot_access) != 0)
        return -1;
    if (villager->data->druid_called == 0) {
        villager->data->druid_called = 1;
        display_pano_wakeup(villager);
        if (sem_post(&villager->data->wake_up_druid) != 0) {
            pthread_mutex_unlock(&villager->data->pot_access);
            return -1;
        }
    }
    villager->data->villagers_waiting++;
    if (pthread_mutex_unlock(&villager->data->pot_access) != 0)
        return -1;
    return 0;
}

int wait_for_refill(villager_t *villager)
{
    if (sem_wait(&villager->data->pot_full) != 0)
        return -1;
    if (pthread_mutex_lock(&villager->data->pot_access) != 0)
        return -1;
    villager->data->villagers_waiting--;
    if (pthread_mutex_unlock(&villager->data->pot_access) != 0)
        return -1;
    return is_druid_alive(villager) ? 1 : 0;
}

int wake_up_druid(villager_t *villager)
{
    if (!is_druid_alive(villager))
        return 0;
    if (call_druid(villager) != 0)
        handle_villager_failure(villager);
    return wait_for_refill(villager);
}
