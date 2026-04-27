/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "panoramix.h"

void free_panoramix(panoramix_t *data)
{
    free(data->params);
    free(data);
}
