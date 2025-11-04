/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "panoramix.h"

druid_t *create_druid(panoramix_t *data)
{
    druid_t *druid = malloc(sizeof(druid_t));

    if (!druid)
        return NULL;
    druid->data = data;
    druid->nb_refills_left = data->params->nb_refills;
    return druid;
}
