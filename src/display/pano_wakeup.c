/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** pano_wakeup
*/

#include <unistd.h>
#include "my_lib.h"
#include "panoramix.h"

void display_pano_wakeup(villager_t *villager)
{
    if (!villager)
        return;
    if (pthread_mutex_lock(&villager->data->print_access) != 0)
        return;
    write(STDOUT_FILENO, "Villager ", 9);
    my_putnbr(villager->id);
    write(STDOUT_FILENO, ": Hey Pano wake up! We need more potion.\n", 41);
    if (pthread_mutex_unlock(&villager->data->print_access) != 0)
        return;
}
