/*
** env.c for minishell in /home/raphael.goulmot/rendu/PSU_2016_minishell2
** 
** Made by Raphaël Goulmot
** Login   <raphael.goulmot@epitech.net>
** 
** Started on  Sat Apr  1 04:51:24 2017 Raphaël Goulmot
** Last update Mon Apr  3 13:48:51 2017 Raphaël Goulmot
*/

#include "utils.h"
#include <stdlib.h>

int	my_env(char **env, char **useless)
{
  while (env && *env)
    {
      my_putstr(*env++);
      my_putchar('\n');
    }
  return (0);
}

int	my_setenv(char **env, char **args)
{
  int	size;
  char	**line;
  char	*value;

  size = env ? my_strstrlen(args) : 0;
  if (size == 1)
    return (my_env(env, args));
  else if (size >= 2 && size <= 3 && !(value = 0))
    {
      while (!value && env && *env)
	{
	  line = split(*env, '=');
	  if (line && my_strstrlen(line) && my_strcmp(line[0], args[1]))
	    value = *env;
	  env += !value ? 1 : 0;
	  free_wordtab(line);
	}
      value = my_strcpy(args[1], "=");
      (env ? *env++ = (size == 2 ? value : my_strcpy(value, args[2])) : 0);
      free(value);
      (env ? *env = 0 : 0);
    }
  else
    my_putstr_err("setenv: Too many arguments.\n");
  return (size > 3 ? 1 : 0);
}

int	my_unsetenv(char **env, char **args)
{
  int	size;
  char	**clone;
  char	find;
  char	**line;

  size = my_strstrlen(args);
  if (size == 1)
    my_putstr_err("unsetenv: Too few arguments.\n");
  else
    {
      while (args && *(++args) && !(find = 0))
	{
	  clone = env;
	  while (clone && *clone && ++clone && (line=split(*(clone - 1), '=')))
	    {
	      if (line && my_strstrlen(line) && my_strcmp(line[0], *args))
		find = 1;
	      *(clone - 1 - find) = *(clone - 1);
	      if (line)
		free_wordtab(line);
	    }
	  *(clone - find - 1) = 0;
	}
    }
  return (size == 1 ? 1 : 0);
}
