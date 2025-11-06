/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** pot
*/

#include "panoramix.h"
#include "errors.h"

int get_pot_from_villager(villager_t *villager)
{
    int result = 0;

    if (pthread_mutex_lock(&villager->data->pot_access) != 0)
        handle_villager_failure(villager);
    result = villager->data->pot;
    if (result > 0)
        villager->data->pot--;
    if (pthread_mutex_unlock(&villager->data->pot_access) != 0)
        handle_villager_failure(villager);
    return result;
}
