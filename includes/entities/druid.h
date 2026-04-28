/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef UNTITLED_DRUID_H
    #define UNTITLED_DRUID_H
    #include "panoramix.h"

druid_t *create_druid(panoramix_t *data);
void *druid_work(void *raw_data);
void free_druid_thread(pthread_t *druid_thread);

#endif
