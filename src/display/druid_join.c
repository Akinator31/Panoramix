/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** druid_join
*/

#include <unistd.h>
#include <stdio.h>
#include "my_lib.h"
#include "panoramix.h"

void display_druid_join(druid_t *druid)
{
    if (!druid)
        return;
    if (pthread_mutex_lock(&druid->data->print_access) != 0) {
        return;
    }
    write(STDOUT_FILENO, "Druid: I'm ready... but sleepy...\n", 34);
    if (pthread_mutex_unlock(&druid->data->print_access) != 0)
        return;
}
