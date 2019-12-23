/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ekran.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 21:00:17 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/23 17:31:43 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	calculate_new_len(char *old_str)
{
	int		i;
	int		len_new_str;

	i = -1;
	len_new_str = ft_strlen(old_str);
	while (old_str[++i])
	{
		if (old_str[i] == '\\')
		{
			if (old_str[i + 1] == '\0')
				return (-1);
			++i;
			--len_new_str;
		}
		else if (old_str[i] == '\'' || old_str[i] == '"')
		{
			--len_new_str;
		}
	}
	return (len_new_str);
}

char		*del_ekran(char *old_str)
{
	int		i;
	int		j;
	int		len_new_str;
	char	*new_str;

	if (!old_str || (len_new_str = calculate_new_len(old_str)) == -1)
		return (0);
	if ((new_str = ft_strnew(len_new_str)) == 0)
		return (0);
	i = -1;
	j = -1;
	while (old_str[++i])
	{
		if (old_str[i] == '\\')
			++i;
		else if (old_str[i] == '\'' || old_str[i] == '"')
			continue ;
		new_str[++j] = old_str[i];
	}
	free(old_str);
	return (new_str);
}
