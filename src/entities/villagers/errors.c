/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** errors
*/

#include <stdlib.h>
#include <stdio.h>
#include "panoramix.h"

void handle_villager_failure(villager_t *villager)
{
    if (villager)
        free(villager);
    perror("An error occured on villagers !");
    exit(EXIT_FAILURE);
}
