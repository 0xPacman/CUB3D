/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:51:35 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/02 21:48:11 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int ft_tablen(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int check_cub(char *filename)
{
    char **splitted;
    
    splitted = ft_split(filename, '.');
    if (!splitted)
        return (0);
    //map.cub.cub should be valid
    if (!ft_strncmp(splitted[ft_tablen(splitted) - 1], "cub", 3))
    {
        ft_free_tab(splitted);
        return (1);
    }
    ft_free_tab(splitted);
    return (0);
}

int main(int ac, char **av) {

    if (ac != 2 || !check_cub(av[1]))
    {
        print_error(0);
        return (0);
    }
    (void)av;


    return (0);
} 