/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** No file there, just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"
#include "parse.h"
#include "help.h"

int get_arg(char *raw_arg)
{
    int arg = strtol(raw_arg, NULL, 10);

    if (arg <= 0)
        return 0;
    return arg;
}

panoramix_params_t *parse_panoramix(int argc, char **argv)
{
    panoramix_params_t *panoramix = NULL;

    if (argc != PANORAMIX_ARG_NUMBER + 1)
        return NULL;
    panoramix = malloc(sizeof(panoramix_params_t));
    if (!panoramix)
        return NULL;
    panoramix->nb_villagers = get_arg(argv[1]);
    panoramix->pot_size = get_arg(argv[2]);
    panoramix->nb_fights = get_arg(argv[3]);
    panoramix->nb_refills = get_arg(argv[4]);
    if (!panoramix->nb_villagers || !panoramix->pot_size ||
        !panoramix->nb_fights || !panoramix->nb_refills) {
        help(NEGETIVE_ARG);
        return NULL;
    }
    return panoramix;
}

void print_panoramix(panoramix_params_t *panoramix)
{
    if (!panoramix)
        return;
    printf("nb_villagers : %d\n", panoramix->nb_villagers);
    printf("pot_size : %d\n", panoramix->pot_size);
    printf("nb_fights : %d\n", panoramix->nb_fights);
    printf("nb_refills : %d\n", panoramix->nb_refills);
}
