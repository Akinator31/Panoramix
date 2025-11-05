/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** fight
*/

#include <unistd.h>
#include "my_lib.h"
#include "panoramix.h"

void display_fight(villager_t *villager)
{
    if (!villager)
        return;
    if (pthread_mutex_lock(&villager->data->print_access) != 0)
        return;
    write(STDOUT_FILENO, "Villager ", 9);
    my_putnbr(villager->id);
    write(STDOUT_FILENO, ": Take that roman scum! Only ", 29);
    my_putnbr(villager->nb_fights);
    write(STDOUT_FILENO, " left.\n", 7);
    if (pthread_mutex_unlock(&villager->data->print_access) != 0)
        return;
}
