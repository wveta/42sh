/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntrl_subst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:42:51 by wveta             #+#    #+#             */
/*   Updated: 2019/12/03 13:19:13 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_read_subst(int fd, int vid, char *str)
{
	struct timespec	clock1;
	struct timespec	clock2;
	char			buf[2];

	clock1.tv_nsec = 100000000;
	clock1.tv_sec = 0;
	nanosleep(&clock1, &clock2);
	buf[0] = '\0';
	while (read(fd, &buf, 1) > 0)
	{
		buf[1] = '\0';
		if (vid == 0 && buf[0] == '\n')
			buf[0] = ' ';
		str = ft_strfjoin(str, buf);
		buf[0] = '\0';
	}
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

char	*ft_go_subst(char *str, int vid)
{
	char			*tmp;
	int				fd;

	tmp = ft_strdup("/tmp/");
	tmp = ft_add_strnum(tmp, getpid());
	tmp = ft_strfjoin(tmp, "_");
	tmp = ft_add_strnum(tmp, g_subs_counter);
	g_subs_counter++;
	str = ft_strfjoin(str, " >");
	str = ft_strfjoin(str, tmp);
	ft_parse_line(str);
	str[0] = '\0';
	if ((fd = open(tmp, O_RDONLY, 0644)) > -1)
	{
		str = ft_read_subst(fd, vid, str);
		close(fd);
	}
	free(tmp);
	return (str);
}

char	**ft_cnt_subs_exe(char **str, int n, int start, int end)
{
	char	*tmp;
	char	*pref;
	char	*suff;

	if (start == -1 || end == -1)
		return (str);
	pref = NULL;
	suff = NULL;
	if (end - start > 1 && str[n][start + 1] != '(')
	{
		if (start > 2)
			pref = ft_strndup(str[n], start - 1);
		if (str[n][end + 1] != '\0')
			suff = ft_strdup(str[n] + end + 1);
		tmp = ft_strdup(str[n] + start + 1);
		tmp[end - start - 1] = '\0';
		tmp = ft_go_subst(tmp, ft_check_ekran(str[n], start - 1));
		str[n][0] = '\0';
		str[n] = ft_strfjoin(str[n], pref);
		str[n] = ft_strfjoin(str[n], tmp);
		str[n] = ft_strfjoin(str[n], suff);
		free(tmp);
		free(pref);
		free(suff);
	}
	return (str);
}

char	**ft_cnt_subs_tst(char **str, int n)
{
	int		i;
	int		qflag;
	int		br_count;
	int		br_flag;
	int		start;
	int		end;

	i = -1;
	start = -1;
	end = -1;
	br_count = 0;
	br_flag = 0;
	qflag = 0;
	while (str && str[n] && str[n][++i])
	{
		if (qflag == 0 && (br_flag == 0 || br_flag == 1) &&
		str[n][i] == '(' && (i == 0 || ft_strchr(" ;|&$", str[n][i - 1])))
		{
			br_flag = 1;
			br_count++;
		}
		else if (qflag == 0 && br_flag == 1 && str[n][i] == '(')
			br_count++;
		else if (qflag == 0 && (br_flag == 0 || br_flag == 2) &&
		str[n][i] == '{' && (i == 0 || ft_strchr(" ;|&", str[n][i - 1])))
		{
			br_flag = 2;
			br_count++;
		}
		else if (qflag == 0 && br_flag == 1 && str[n][i] == '{')
			br_count++;
		if (qflag == 0 && ((br_flag == 1 && str[n][i] == ')') ||
		(br_flag == 2 && str[n][i] == '}')))
		{
			br_count--;
			if (br_count == 0)
			{
				br_flag = 0;
				if (start != -1 && str[n][start + 1] != '(' && ((end = i)))
				{
					str = ft_cnt_subs_exe(str, n, start, end);
					i = -1;
					continue;
				}
			}
		}
		if ((qflag == 2 && str[n][i] == '\'' &&
		(i == 0 || str[n][i - 1] != '\\')))
			qflag = 0;
		else if (qflag == 0 && str[n][i] == '\'' &&
		(i == 0 || str[n][i - 1] != '\\'))
			qflag = 2;
		if (qflag == 0 && br_flag == 0 && (i == 0 || str[n][i - 1] != '\\')
		&& str[n][i] == '$' && str[n][i + 1] && str[n][i + 1] == '(')
			start = i + 1;
	}
	return (str);
}

char	**ft_cnt_subs(char **av)
{
	int		i;

	i = -1;
	while (av && av[++i])
	{
		av = ft_cnt_subs_tst(av, i);
	}
	return (av);
}
