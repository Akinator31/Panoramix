/*
** EPITECH PROJECT, 2026
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
int wake_up_druid(villager_t *villager);
void handle_villager_failure(villager_t *villager);

#endif
