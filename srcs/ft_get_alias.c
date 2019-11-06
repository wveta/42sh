/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 10:57:37 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/04 18:30:48 by wveta            ###   ########.fr       */
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
	while (tmp[i] && tmp[i] != '\n')
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
	if ((result =
			(char **)malloc(sizeof(char *) * (len_new + (len_ret - 1) + 1))) == NULL)
		ft_print_msg(": ft_add_arr:" ," Malloc can't allocate the memory!");
	else
	{
		i = -1;
		while (++i < len_new)
			result[i] = new[i];
		j = 1;
		while (j < len_ret)
		{
			result[i] = ret[j];
			++j;
			++i;
		}
		result[i] = 0;
	}
	return (result);
}

char					**ft_get_alias(char **av)
{
	char				**ret;
	char				**tmp;
	char				*ans;
	char				**new;
	char				*all_alias;

	ret = av;
	all_alias = ft_read_alias();
	while (all_alias && (ans = take_value_alias(all_alias, ret[0])) != NULL)
	{
		if ((new = ft_strsplit(ans, ' ')) == NULL)
		{
			ft_print_msg(": ft_get_alias:",
						" Maloc can't allocate the memory!");
			ft_strdel(&ans);
			break ;
		}
		tmp = ft_add_arr(new, ret);
		ft_strdel(&ans);
		free(new);
		if (tmp == NULL)
			break ;
		free(ret);
		ret = tmp;
	}
	ft_strdel(&all_alias);
	return (ret);
}
