/*
** EPITECH PROJECT, 2026
** panoramix
** File description:
** my_putchar
*/

#include <unistd.h>

int my_putchar(char c)
{
    write(1, &c, 1);
}
