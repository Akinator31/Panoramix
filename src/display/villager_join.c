/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** join
*/

#include <unistd.h>
#include "my_lib.h"
#include "panoramix.h"

void display_villager_join(villager_t *villager)
{
    if (!villager)
        return;
    if (pthread_mutex_lock(&villager->data->print_access) != 0)
        return;
    write(STDOUT_FILENO, "Villager ", 9);
    my_putnbr(villager->id);
    write(STDOUT_FILENO, ": Going into battle!\n", 21);
    if (pthread_mutex_unlock(&villager->data->print_access) != 0)
        return;
}
