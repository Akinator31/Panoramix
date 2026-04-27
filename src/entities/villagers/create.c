/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "panoramix.h"

villager_t *create_villager(int id, panoramix_t *data)
{
    villager_t *villager = malloc(sizeof(villager_t));

    if (!villager || !data)
        return NULL;
    villager->id = id;
    villager->data = data;
    villager->nb_fights = data->params->nb_fights;
    return villager;
}
