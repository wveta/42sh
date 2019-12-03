/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntrl_subst2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:42:51 by wveta             #+#    #+#             */
/*   Updated: 2019/12/03 15:28:58 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_resize_matr(char **str, int n)
{
	int		i;
	int		add;
	char	**ret;
	char	**tmp;
	int		j;

	i = ft_calc_matr_rows(str);
	ret = str;
	if ((add = ft_split_pipes_words(str[n])) > 1)
	{
		tmp = ft_split_pipes(str[n]);
		ret = (char **)malloc(sizeof(char *) * (i + add));
		ret[i + add - 1] = NULL;
		j = -1;
		while (++j < i + add)
		{
			if (j < n)
				ret[j] = str[j];
			else if (j >= n && j <= n + add - 1)
				ret[j] = tmp[j - n];
			else
				ret[j] = str[j - (n + add - 1) + 1];
		}
		free(str);
		free(tmp);
	}
	return (ret);
}
