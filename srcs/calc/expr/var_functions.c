/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:13:02 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/22 11:21:05 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					take_var_value(char *name)
{
	char				*value;
	int32_t				ans;
	uint32_t			len_numb;
	uint32_t			sign;
	uint32_t			i;

	ans = 0;
	len_numb = 0;
	sign = 0;
	value = ft_get_env(name);
	if (value)
	{
		i = 0;
		while (value[i] && is_it_spaces(value[i]) == SUCCESS)
			++i;
		while (value[i] && (value[i] == '-' || value[i] == '+'))
		{
			if (value[i] == '-')
				sign = !sign;
			++i;
		}
		if (ft_strncmp("0x", &value[i], 2) == 0 || ft_strncmp("0X", &value[i], 2) == 0)
			ans = ft_atoi_base(&value[i] + 2, 16, &len_numb);
		else if (ft_strncmp("0", &value[i], 1) == 0)
			ans = ft_atoi_base(&value[i] + 1, 8, &len_numb);
		else
			ans = ft_atoi_base(&value[i], 10, &len_numb);
		ft_strdel(&value);
	}
	if (sign)
		ans = -ans;
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
