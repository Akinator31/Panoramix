/*
** EPITECH PROJECT, 2025
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

    if (!villager)
        return NULL;
    villager->id = id;
    villager->data = data;
    return villager;
}