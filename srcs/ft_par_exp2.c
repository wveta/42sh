/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/05 18:54:34 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_test_parname(char *str)
{
	int i;

	i = -1;
	while(str && str[++i])
	{
		if ((i == 0 && (!(ft_isalpha(str[i]))) && (!(ft_strchr("_?", str[i]))))
		|| ft_strchr(" ", str[i]) || (!(ft_isalnum(str[i]))))
			return (1);
	}
	return (0);
}

char	*ft_print_badsub(char *s, int i, char *tmp)
{
	g_subs_rc = 1;
	if (i == 0)
		ft_print_msg(": bad substitution : ", s);
	else if (i == 1)
	{
		ft_print_msg(": parameter null or not set: ", tmp);
		free(tmp);
	}
	ft_set_shell("?", "1");
	if (g_subshell != 0)
		exit_shell(1);
	return (s);
}

int		ft_subst_lbr(char *s)
{
	int i;
	int nbr;

	i = -1;
	nbr = 1;
	while (s && s[++i])
	{
		if (s[i] == '{' && ft_check_ekran(s, i) == 0)
			nbr++;
		else if (s[i] == '}' && ft_check_ekran(s, i) == 0)
		{
			nbr--;
			if (nbr == 0)
				return (i);
		}
	}
	return (-1);
}
