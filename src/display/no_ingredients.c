/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** no_ingredients
*/

#include <unistd.h>
#include "my_lib.h"
#include "panoramix.h"

void display_no_more_ingredients(druid_t *druid)
{
    if (!druid)
        return;
    if (pthread_mutex_lock(&druid->data->print_access) != 0)
        return;
    write(STDOUT_FILENO, "Druid: I'm out of viscum. I'm going back to... zZz\n", 51);
    if (pthread_mutex_unlock(&druid->data->print_access) != 0)
        return;
}
