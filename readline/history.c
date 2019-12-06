/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:09:13 by thaley            #+#    #+#             */
/*   Updated: 2019/12/06 15:00:48 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_history_put(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(g_hist->path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd > 0)
	{
		while (g_hist->cmd[i])
		{
			write(fd, g_hist->cmd[i], ft_strlen(g_hist->cmd[i]));
			free(g_hist->cmd[i]);
			i++;
		}
		close(fd);
		free(g_hist->path);
		free(g_hist->cmd);
		g_hist->cmd = NULL;
		free(g_hist);
	}
}

static void	hist_from_file(void)
{
	int		len;
	int		fd;
	char	tmp[MAX_CMDS];
	char	*buf;

	buf = NULL;
	len = 0;
	ft_bzero(tmp, MAX_CMDS);
	if ((fd = open(g_hist->path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return ;
	while ((get_next_line(fd, &buf)) > 0)
	{
		len = ft_strlen(buf);
		g_hist->cmd[g_hist->amount] = ft_strjoin(g_hist->cmd[g_hist->amount], buf);
		if (len >= 2 && buf[len - 2] == 7)
			g_hist->amount++;
		free(buf);
		buf = NULL;
	}
	g_hist->cmd[g_hist->amount] = NULL;
}

void		create_history(void)
{
	char	*tmp;

	tmp = NULL;
	if (!(g_hist = (t_hist *)malloc(sizeof(t_hist))))
		mall_check();
	if (!(g_hist->cmd = (char **)malloc(sizeof(char *) * 101)))
		mall_check();
	int i = -1;
	while (++i < 101)
		g_hist->cmd[i] = NULL;
	// ft_bzero(g_hist->cmd, 101);
	if ((tmp = ft_get_my_home()))
	{
		g_hist->path = ft_strjoin(tmp, "/.history");
		free(tmp);
	}
	g_hist->amount = 0;
	hist_from_file();
	g_hist->pos = g_hist->amount;
}
