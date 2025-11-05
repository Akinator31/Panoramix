/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** drink
*/

#include <unistd.h>
#include "my_lib.h"
#include "panoramix.h"

void display_need_to_drink(villager_t *villager, int servings_left)
{
    if (!villager)
        return;
    if (pthread_mutex_lock(&villager->data->print_access) != 0)
        return;
    write(STDOUT_FILENO, "Villager ", 9);
    my_putnbr(villager->id);
    write(STDOUT_FILENO, ": I need a drink... I see ", 26);
    my_putnbr(servings_left);
    write(STDOUT_FILENO, " servings left.\n", 16);
    if (pthread_mutex_unlock(&villager->data->print_access) != 0)
        return;
}
