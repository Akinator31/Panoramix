/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdarg.h>
#include "panoramix.h"

void free_panoramix(panoramix_t *data)
{
    free(data->params);
    free(data);
}

void my_free(int count, ...)
{
    va_list args;

    va_start(args, count);
    for (int i = 0; i < count; i++)
        free(va_arg(args, void *));
    va_end(args);
}
