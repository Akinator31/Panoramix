/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include "help.h"

void help(error_code_t error_code)
{
    fprintf(stderr, "USAGE: ./panoramix <nb_villagers> <pot_size>"
        "<nb_fights> <nb_refills>\n");
    if (error_code == NEGETIVE_ARG) {
        fprintf(stderr, "Values must be >0.\n");
    }
}
