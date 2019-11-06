/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/11/01 22:17:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_insert_subshell(char *str, int start, int end)
{
	char	*tmp;
	int		len;

	if (start >= 0 && end - start > 1)
	{
		len = 5 + 3 + 1 + ft_strlen(str) + ft_strlen(g_app_full_name);
		if (!(tmp = malloc(sizeof(char) * len)))
			return (NULL);
		tmp[0] = '\0';
		tmp = ft_strcpy(tmp, "echo '");
		ft_strncpy(tmp + 6 , str + start + 1, end - start - 1);
		ft_strcpy(tmp + 6 + end - start - 1, "' | ");
		ft_strcpy(tmp + 6 + end - start - 1 + 4, g_app_full_name);
		tmp = ft_strfjoin(tmp, str + end + 1);
		free(str);
		str = tmp;
	}
	return (str);
}

char		*ft_test_subshell(char *strin, int start)
{
	int 	i;
	int 	qflag;
	int 	shstart;
	int 	shfinish;
	char 	*str;

	i = 0;
	qflag = 0;
	shstart = -1;
	shfinish = 0;
	str = ft_strdup(strin);
	while (str && str[i + start])
	{
		if (shstart == -1 && ft_isspace(str[i + start]))
			continue ;
		else if (shstart == -1)
		{
			shstart = i;
			if (str[i + start] != '(')
				return (ft_strdup(str));
		}
		if (qflag == 0 && str[i + start] == '"')
			qflag = 1;
		else if ((qflag == 1 && str[i + start] == '"') ||
			(qflag == 2 && str[i] == '\''))
			qflag = 0;
		else if (qflag == 0 && str[i + start] == '\'')
			qflag = 2;
		if (qflag == 0 && (str[i + start] == ')'))
		{
			shfinish = i;
			str = ft_insert_subshell(str, shstart, shfinish);
			i = i + 8 + ft_strlen(g_app_full_name);
		}
		i++;
	}
	return (str);
}
