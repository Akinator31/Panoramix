/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** cook
*/

#include <unistd.h>
#include "my_lib.h"
#include "panoramix.h"

void display_cooking(druid_t *druid)
{
    if (pthread_mutex_lock(&druid->data->print_access) != 0)
        return;
    write(STDOUT_FILENO, "Druid: Ah! Yes, yes, I'm awake! Working on it! ", 47);
    write(STDOUT_FILENO, "Beware I can only make ", 23);
    my_putnbr(druid->nb_refills_left - 1);
    write(STDOUT_FILENO, " more refills after this one.\n", 30);
    if (pthread_mutex_unlock(&druid->data->print_access) != 0)
        return;
}
