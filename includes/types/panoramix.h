/*
** EPITECH PROJECT, 2026
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef UNTITLED_PANORAMIX_H
#define UNTITLED_PANORAMIX_H
#define CHECK(call, clean) ((call) == -1 ? (clean, 1) : 0)
#include <pthread.h>
#include <semaphore.h>

typedef struct panoramix_params_s {
  int nb_villagers;
  int pot_size;
  int nb_fights;
  int nb_refills;
} panoramix_params_t;

typedef struct panoramix_s {
  sem_t wake_up_druid;
  sem_t pot_full;
  pthread_mutex_t pot_access;
  pthread_mutex_t print_access;
  panoramix_params_t *params;
  int druid_called;
  int druid_alive;
  int villagers_waiting;
  int pot;
} panoramix_t;

typedef struct villager_s {
  int id;
  int nb_fights;
  panoramix_t *data;
} villager_t;

typedef struct druid_s {
  int nb_refills_left;
  panoramix_t *data;
} druid_t;

#endif
