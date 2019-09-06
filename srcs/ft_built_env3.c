/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/09/06 20:47:50 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_exp_name(char *str, int j)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) || str[i] == '?' || str[i] == '_')
	{
		while (str[++i] && i < j)
		{
			if (!(ft_isalpha(str[i]) || ft_isdigit(str[i])))
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_unset_env_parm(char *str)
{
	int i;

	i = 0;
	if ((i = ft_get_ind_env(str, g_envi->env)) != -1)
	{
		free(g_envi->env[i]);
		while (g_envi->env[i])
		{
			g_envi->env[i] = g_envi->env[i + 1];
			i++;
		}
	}
}
