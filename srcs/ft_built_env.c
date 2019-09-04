/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/08/06 21:06:19 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_add_env(char *str)
{
	int		i;
	char	*s;

	if (!(g_envi->env))
		i = 1;
	else
	{
		i = 0;
		while (g_envi->env[i] && g_envi->env[i] != NULL)
			i++;
	}
	s = g_envi->env[i - 1];
	g_envi->env[i] = s;
	g_envi->env[i - 1] = str;
	g_envi->env[i + 1] = NULL;
	return (g_envi->env);
}

char	*ft_get_env(char *parm)
{
	int	i;
	int	j;

	if (g_envi->env)
	{
		i = 0;
		j = ft_strlen(parm);
		while (g_envi->env[i])
		{
			if (ft_strnequ(parm, g_envi->env[i], j) == 1 &&
			g_envi->env[i][j] == '=')
				return (ft_strdup(g_envi->env[i] + j + 1));
			i++;
		}
	}
	return (NULL);
}

char	**ft_set_env(char *parm, char *value)
{
	int		i;
	char	*str;

	if (!(value))
		return (g_envi->env);
	if (!(str = malloc(sizeof(char) * (2 + ft_strlen(parm) +
		ft_strlen(value)))))
		exit_shell();
	str[0] = '\0';
	str = ft_strcat(str, parm);
	str = ft_strcat(str, "=");
	str = ft_strcat(str, value);
	if ((i = ft_get_ind_env(parm)) != -1)
	{
		free(g_envi->env[i]);
		g_envi->env[i] = str;
	}
	else
	{
		g_envi->env = ft_add_env(str);
	}
	if ((i = ft_strequ(parm, "PATH")) == 1)
		ft_reset_cmd_list();
	return (g_envi->env);
}

int		ft_unset_env(char *parm)
{
	int i;

	if ((i = ft_get_ind_env(parm)) != -1)
	{
		free(g_envi->env[i]);
		while (g_envi->env[i])
		{
			g_envi->env[i] = g_envi->env[i + 1];
			i++;
		}
	}
	i = 0;
	if ((i = ft_strequ(parm, "PATH")) == 1)
		ft_reset_cmd_list();
	return (1);
}
