/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 10:57:37 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/28 15:06:05 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char					*take_value_alias(char *all_alias, char *alias_name)
{
	char				*value;
	char				*tmp;
	int					i;

	tmp = ft_find_alias(all_alias, alias_name);
	if (tmp == NULL)
		return (0);
	tmp += ft_strlen(alias_name) + 2;
	i = 0;
	while (tmp[i] && tmp[i] != -10)
		++i;
	if (tmp[i - 1] == '"')
		--i;
	if ((value = ft_strndup(tmp, i)) == NULL)
		ft_print_msg(": ft_get_alias:", " Malloc can't allocate the memory!");
	return (value);
}

static char				**ft_add_arr(char **new, char **ret)
{
	char				**result;
	int					len_new;
	int					len_ret;
	int					i;
	int					j;

	len_new = ft_arr_len(new);
	len_ret = ft_arr_len(ret);
	result = 0;
	if ((result = (char **)malloc(sizeof(char *) *
							(len_new + (len_ret - 1) + 1))) == NULL)
		ft_print_msg(": ft_add_arr:", " Malloc can't allocate the memory!");
	else
	{
		i = -1;
		while (++i < len_new)
			result[i] = ft_strdup(new[i]);
		j = 0;
		while (++j < len_ret)
			result[i++] = ft_strdup(ret[j]);
		result[i] = 0;
	}
	return (result);
}

static void				ft_del_arr(char ***arr)
{
	int32_t				i;

	i = -1;
	while ((*arr)[++i])
	{
		ft_strdel(&(*arr)[i]);
	}
	free(*arr);
	arr = 0;
}

static char				**ft_prep_for_add_arr(char **ans, char **av)
{
	char				**tmp;
	char				**new;

	new = ft_strsplit(*ans, ' ');
	ft_strdel(ans);
	if (new == NULL)
	{
		ft_print_msg(": ft_get_alias:",
				" Malloc can't allocate the memory!");
		return (0);
	}
	tmp = ft_add_arr(new, av);
	ft_del_arr(&new);
	return (tmp);
}

char					**ft_get_alias(char **av)
{
	char				**tmp;
	char				*ans;
	char				*all_alias;
	char				*first;

	if (av[0] && ft_strlen(av[0]) == 0)
		return (av);
	all_alias = ft_read_alias();
	first = ft_strdup(av[0]);
	while (all_alias && (ans = take_value_alias(all_alias, av[0])) != NULL)
	{
		tmp = ft_prep_for_add_arr(&ans, av);
		if (tmp == NULL)
			break ;
		ft_del_arr(&av);
		av = tmp;
		if (ft_strequ(av[0], first) == 1)
			break ;
	}
	ft_strdel(&first);
	ft_strdel(&all_alias);
	return (av);
}
