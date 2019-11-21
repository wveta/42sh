/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:13:02 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/21 16:05:52 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					take_var_value(char *name)
{
	char				*value;
	int32_t				ans;

	ans = 0;
	value = ft_get_env(name);
	if (value)
	{
		ans = ft_atoi(value);
		ft_strdel(&value);
	}
	return (ans);
}

void					change_var_value(char *name, int32_t operation)
{
	int32_t				ans;
	int					i;
	char				*value;
	char				*var_node;

	ans = take_var_value(name);
	if (operation == INCREMENT)
		++ans;
	else
		--ans;
	value = ft_itoa(ans);
	var_node = ft_strjoin(name, "=");
	var_node = ft_strfjoin(var_node, value);
	if ((i = ft_get_ind_env(name, g_shell)) == -1)
		g_shell = ft_add_shell(ft_strdup(var_node), g_shell);
	else
	{
		ft_strdel(&g_shell[i]);
		g_shell[i] = ft_strdup(var_node);
	}
	if ((i = ft_get_ind_env(name, g_envi->env)) != -1)
	{
		ft_strdel(&g_envi->env[i]);
		g_envi->env[i] = ft_strdup(var_node);
	}
	ft_strdel(&var_node);
	ft_strdel(&value);
}
