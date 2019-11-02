/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_for_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:40:26 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/02 09:46:41 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					ft_arr_len(char **av)
{
	int			len;

	len = 0;
	while (av && av[len])
		++len;
	return (len);
}

void				ft_change_alias(char *new_alias)
{
	int				len;
	int				fd;

	len = ft_strlen(new_alias);
	if ((fd = open("/Users/udraugr-/.alias_42",
					O_CREAT | O_TRUNC | O_WRONLY, 0x1FF)) == -1)
		ft_print_msg("'Open' cant read the file!", "");
	else
		write(fd, new_alias, len);
}

char				*ft_find_alias(char *str, char *alias)
{
	char			*tmp;
	char			*ans;
	int				len_alias;

	len_alias = ft_strlen(alias);
	tmp = ft_strnew(len_alias + 1);
	ft_strncpy(tmp, alias, len_alias);
	tmp[len_alias] = '=';
	ans = ft_strstr(str, tmp);
	ft_strdel(&tmp);
	return (ans);
}
