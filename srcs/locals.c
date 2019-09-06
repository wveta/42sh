/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/06 15:29:53 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_init_shell(void)
{
	int i;
	
	i = ft_calc_matr_rows(g_envi->env);
	if (!(g_shell = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	g_shell[i + 1] = NULL;
	i = -1;
	while (g_envi->env[++i])
		g_shell[i] = ft_strdup(g_envi->env[i]);
	if (!(g_shell[i] = ft_strdup("?=0")))
	{
		ft_free_char_matr(g_shell);
		g_shell = NULL;
		return (g_shell);
	}
	return (g_shell);
}

void	ft_init_glvar(char **av)
{
	g_app_name = ft_get_app_name(av[0]);
	g_check = 0;
	g_color = 1;
	g_shell = NULL;
	g_shell = ft_init_shell();
}
