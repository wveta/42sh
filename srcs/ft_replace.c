/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/11 21:32:14 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_repl_parm(char *s, int flag, int len)
{
	int		j;
	char	q;
	int		k;

	j = -1;
	q = ' ';
	while (++j < len)
	{
		k = ft_repl_check(s, len, &q, j);
		if (k == 1)
			continue;
		else if (k == -1)
		{
			j--;
			continue;
		}
		if (q == ' ' && flag == 1)
			s = ft_repl_end_til(s, j, &flag);
		else if (q != '\'' && s[j] == '$' && ft_check_ekran(s, j) == 0 &&
		(k != 2) && s[j + 1] &&
		(s[j + 1] == '_' || ft_isalpha(s[j + 1]) || s[j + 1] == '?' ||
		s[j + 1] == '{'))
		{
			if (flag == 1)
			{
				flag = 0;
				s = ft_repl_tilda(s, j);
			}
			s = ft_repl_env(s, &j);
			if (g_subs_rc == 0)
				j--;
			else
				return (s);
		}
		len = ft_strlen(s);
	}
	if (flag == 1)
		s = ft_repl_tilda(s, j);
	return (s);
}

int		ft_repl_sym(char *s, int j)
{
	int		i;

	i = 1;
	while (s[j + i])
	{
		if (ft_strchr("!#%@\"\'^*()=\\.:$", s[j + i]))
			break ;
		i++;
	}
	return (i);
}

char	**ft_cmd_replays(char **str)
{
	char	**ret;
	int		i;

	ret = NULL;
	g_subs_rc = 0;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_replays(str[i]);
			i++;
		}
		str = ft_press_matr(str);
		if (!str[0])
		{
			g_subs_rc = 1;
			ft_print_msg(": command not found ", " ");
			ft_set_shell("?", "1");
			if (g_subshell != 0)
				exit_shell(1);
		}
		return (str);
	}
	return (ret);
}
