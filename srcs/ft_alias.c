/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:00:14 by wveta             #+#    #+#             */
/*   Updated: 2019/11/02 10:50:20 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void				ft_output_alias(char *all_alias, char *av,
										int flag_alias, int *ret)
{
	char				*ans;
	int					i;

	if ((ans = ft_find_alias(all_alias, av)) == NULL)
	{
		ft_putstr_fd("42sh: alias: ", 2);
		ft_putstr_fd(av, 2);
		ft_putendl(": not found");
		*ret = 0;
	}
	else
	{
		if (flag_alias)
			ft_putstr("alias ");
		i = 0;
		while (ans[i] && ans[i] != '\n')
			++i;
		write(1, ans, i);
		write(1, "\n", 1);
	}
}

static char				*ft_push_alias(char *all_alias, char *av)
{
	char				*ans;
	int					len_all_alias;
	int					len_ans;
	int					i;

	ans = 0;
	len_all_alias = ft_strlen(all_alias);
	len_ans = len_all_alias + 1 + ft_strlen(av) + 2;
	if ((ans = ft_strnew(len_ans)) == NULL)
		return (0);
	ft_strcpy(ans, all_alias);
	i = 0;
	while (len_all_alias < len_ans)
	{
		ans[len_all_alias] = av[i];
		++len_all_alias;
		++i;
		if (ans[len_all_alias - 1] == '=')
			break ;
	}
	ans[len_all_alias++] = '"';
	ft_strcpy(&ans[len_all_alias], &av[i]);
	ans[len_ans - 2] = '"';
	ans[len_ans - 1] = '\n';
	return (ans);
}

static char				*ft_replace_alias(char *all_alias,
												char *av, char *alias_name)
{
	char				*ans;
	char				*tmp;

	ans = ft_del_alias(ft_strdup(all_alias), alias_name);
	tmp = ft_push_alias(ans, av);
	ft_strdel(&ans);
	ans = tmp;
	return (ans);
}

static char				*ft_add_alias(char *all_alias, char *av)
{
	char				*ans;
	char				*alias_name;
	int					len_av;
	int					len_alias_name;

	len_av = ft_strlen(av);
	ans = 0;
	len_alias_name = ft_strchr(av, '=') - av;
	if ((alias_name = ft_strnew(len_alias_name)) != NULL)
	{
		ft_strncpy(alias_name, av, len_alias_name);
		if (ft_find_alias(all_alias, alias_name) != NULL)
			ans = ft_replace_alias(all_alias, av, alias_name);
		else
			ans = ft_push_alias(all_alias, av);
		ft_strdel(&alias_name);
	}
	if (ans == NULL)
		ft_print_msg("alias:", " Malloc can't alloacte memory!");
	ft_strdel(&all_alias);
	return (ans);
}

/*
** flag p in alias, just print alias until output;
** like:
** __INPUT__
** alias -p aa
** __OUTPUT__
** alias aa="hello"
*/

int						ft_alias(char **av)
{
	int					i;
	char				*all_alias;
	int					flag_alias;
	int					ret;

	if ((all_alias = ft_read_alias()) == NULL)
		return (0);
	ret = 1;
	i = 1;
	flag_alias = 0;
	while (av[i] && ft_strcmp("-p", av[i]) == 0)
	{
		flag_alias = 1;
		++i;
	}
	if (ft_arr_len(&av[i]) < 1)
		write(1, all_alias, ft_strlen(all_alias));
	else
	{
		while (av[i])
		{
			if (ft_strchr(av[i], '=') == NULL)
				ft_output_alias(all_alias, av[i], flag_alias, &ret);
			else
			{
				if ((all_alias = ft_add_alias(all_alias, av[i])) == NULL)
					break ;
			}
			++i;
		}
	}
	ft_change_alias(all_alias);
	ft_strdel(&all_alias);
	return (ret);
}

char	**ft_get_alias(char **av)
{
	char **ret;

	ret = av;
	return (ret);
}
