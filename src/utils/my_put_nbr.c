/*
** my_put_nbr.c for minishell in /home/raphael.goulmot/rendu/Bootstrap_Minishell
** 
** Made by Raphaël Goulmot
** Login   <raphael.goulmot@epitech.net>
** 
** Started on  Wed Jan  4 09:40:53 2017 Raphaël Goulmot
** Last update Fri Mar 31 23:20:17 2017 Raphaël Goulmot
*/

#include "utils.h"

void	my_put_nbr(int nbr)
{
  if (nbr < 0)
    my_putchar('-');
  nbr *= nbr < 0 ? -1 : 1;
  if (nbr > 9)
    my_put_nbr(nbr / 10);
  my_putchar(48 + nbr % 10);
}
