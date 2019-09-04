/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/09/04 21:21:12 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_echo_flag(char *str, int *flag0, int *flag1)
{
	int i;
	int	f1;
	int	f2;

	i = 1;
	f1 = 0;
	f2 = 0;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] == 'n')
			f1 = 1;
		else if (str[i] == 'e')
			f2 = 1;
		else if (str[i] == 'E')
			f2 = 0;
		else
			return (1);
		i++;
	}
	*flag0 = f1;
	*flag1 = f2;
	return (0);
}

void		ft_upr_sym(int flag, char *str)
{
	char	*tmp;
	char	*s;
	int		len;

	if (((len = ft_strlen(str))) && flag == 1)
	{
		s = str;
		while (*s)
		{
			if (s[0] == '\\')
			{
				if ((tmp = ft_strchr(UPR0, s[1])))
				{
					s[0] = tmp - UPR0;
					ft_strcpy(s + 1, s + 2);
					len--;
				}
			}
			s++;
		}
	}
	write(STDOUT_FILENO, str, len);
}

int			ft_echo(char **av)
{
	int		i;
	int		flag[2];
	int		j;

	i = 1;
	j = 0;
	flag[0] = 0;
	flag[1] = 0;
	while (av[i])
	{
		if (ft_echo_flag(av[i], &flag[0], &flag[1]) == 1)
		{
			if (i > j + 1)
				ft_putstr(" ");
			ft_upr_sym(flag[1], av[i]);
		}
		else
			j = i;
		i++;
	}
	if (flag[0] != 1)
		ft_putstr("\n");
	return (1);
}

int			ft_built_in(char *path, char **av)
{
	if (path && ft_strequ(path, "exit") == 1)
	{
		ft_final_free();
		exit(0);
	}
	else if (path && g_envi->env && ft_strncmp(path, "env", 3) == 0)
		return (ft_print_env());
	else if (path && ft_strncmp(path, "cd", 2) == 0)
		return (ft_built_cd(av));
	else if (path && ft_strncmp(path, "setenv", 6) == 0)
	{
		if (ft_calc_matr_rows(av) > 3)
			ft_print_msg(" : incorrect count of arguments: ", path);
		else if (ft_calc_matr_rows(av) == 3)
			g_envi->env = ft_set_env(av[1], av[2]);
		return (1);
	}
	else if (path && ft_strncmp(path, "unsetenv", 8) == 0)
		if (ft_calc_matr_rows(av) != 2)
			ft_print_msg(" : incorrect count of arguments: ", path);
		else
			return (ft_unset_env(av[1]));
	else if (path && ft_strncmp(path, "echo", 4) == 0)
		return (ft_echo(av));
	return (0);
}
