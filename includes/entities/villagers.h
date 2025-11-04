/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef UNTITLED_VILLAGERS_H
    #define UNTITLED_VILLAGERS_H
    #include "panoramix.h"

villager_t *create_villager(int id, panoramix_t *data);
void *villager_work(void *raw_data);
void free_villagers_thread(pthread_t **villagers_threads);
int is_druid_alive(villager_t *villager);

#endif
