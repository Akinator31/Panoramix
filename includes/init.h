/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef UNTITLED_INIT_H
    #define UNTITLED_INIT_H
    #include "panoramix.h"

panoramix_t *init_panoramix_data(panoramix_params_t *params);
pthread_t **init_villagers_threads(panoramix_t *data);
pthread_t *init_druid_thread(panoramix_t *data);

#endif
