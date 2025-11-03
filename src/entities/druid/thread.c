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

void *druid_work(void *raw_data)
{
    druid_t *druid = (druid_t *)raw_data;

    printf("Druid: I'm ready... but sleepy...\n");
    free(druid);
    return NULL;
}

void free_druid_thread(pthread_t *druid_thread)
{
    free(druid_thread);
}
