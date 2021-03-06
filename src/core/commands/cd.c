/*
** cd.c for minishell in /home/raphael.goulmot/rendu/PSU_2016_minishell2
** 
** Made by Raphaël Goulmot
** Login   <raphael.goulmot@epitech.net>
** 
** Started on  Sat Apr  1 04:53:41 2017 Raphaël Goulmot
** Last update Sun Apr  9 17:33:33 2017 Raphaël Goulmot
*/

#include "utils.h"
#include "commands.h"
#include <unistd.h>
#include <stdlib.h>

int	error_handling(char *str, int size, int state, char **args)
{
  if (!str && size == 1)
    my_putstr_err("cd: No home directory.\n");
  else if (str && size == 2 && !my_strcmp(args[1], "-") && state == -1)
    my_putstr_err(args[1]);
  if (state == -1 || (!str && size == 2))
    my_putstr_err(": Not a directory.\n");
  else if (size > 2)
    my_putstr_err("cd: Too many arguments.\n");
  return (!str || size > 2 || state == -1 ? 1 : 0);
}

void	set_var(char ***env, char *var, char *str)
{
  char	**commands;

  commands = malloc(sizeof(char *) * 4);
  commands[0] = "setenv";
  commands[1] = var;
  commands[2] = str;
  commands[3] = 0;
  my_setenv(env, commands);
  free(commands);
}

int	my_cd(char ***env, char **args)
{
  int	size;
  char	*value;
  char	buff[4096];
  int	state;
  char	*path;

  size = args ? my_strstrlen(args) : 1;
  state = 0;
  if (size == 1)
    value = get_var(*env, "HOME");
  else if (size == 2 && my_strcmp(args[1], "-"))
    value = get_var(*env, "OLDPWD");
  else
    value = args[1];
  path = getcwd(buff, 4096);
  if (value && size <= 2)
    {
      state = chdir(value);
      set_var(env, "OLDPWD", path);
    }
  return (error_handling(value, size, state, args));
}
