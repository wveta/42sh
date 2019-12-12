/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 21:00:18 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setqflag(int *qflag, int val, int *wcount)
{
	*qflag = val;
	*wcount = *wcount + 1;
}

void		ft_ini_quoteflag_spl(t_quoteflag *f)
{
	f->i = 0;
	f->br_count = 0;
	f->br_flag = 0;
	f->qflag = 0;
	f->flsub = 0;
	f->b_sl = 0;
	f->i_cmd = 0;
}

int			ft_get_word(char **ret, int count, int size, char const *s)
{
	if (*(s + size) == '\0')
		size = size + 1;
	ret[count] = (char *)malloc(sizeof(char) * (size + 1));
	if (ret[count] == NULL)
		return (-1);
	ret[count][size + 0] = '\0';
	ret[count] = ft_strncpy(ret[count], s, (size_t)(size));
	return (0);
}

char		**ft_split_pipes(char *s)
{
	int		count;
	char	**ret;
	int		myjob;

	if (!s || (count = ft_split_pipes_words(s)) == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (ret == NULL)
		return (NULL);
	else
	{
		ret[count] = NULL;
		if (ft_all_pipe_words(ret, s) == -1 || ft_parse_pipe(ret))
		{
			ft_free_char_matr(ret);
			return (NULL);
		}
	}
	myjob = g_job;
	ret = ft_cnt_subs(ret);
	g_job = myjob;
	ret = ft_resize_matr(ret);
	ret = ft_press_matr(ret);
	return (ret);
}
