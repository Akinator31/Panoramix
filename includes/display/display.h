/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** display
*/

#ifndef DISPLAY_H
#define DISPLAY_H
#include "panoramix.h"

void display_pano_wakeup(villager_t *villager);
void display_villager_join(villager_t *villager);
void display_need_to_drink(villager_t *villager, int servings_left);
void display_fight(villager_t *villager);
void display_sleep(villager_t *villager);
void display_cooking(druid_t *druid);
void display_no_more_ingredients(druid_t *druid);
void display_druid_join(druid_t *druid);

#endif
