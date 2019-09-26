/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_print_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/26 16:08:19 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_job_stop(t_job *cur_job)
{
	char	*tmp;

	if ((tmp = ft_print_job_pref(cur_job)))
	{
		tmp = ft_strfjoin(tmp, "  Stopped               ");
		tmp = ft_strfjoin(tmp, cur_job->orig_cmd);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}

void	ft_print_jobs(void)
{
	t_job	*job;
	t_proc	*proc;

	job = g_job_first;
	while (job)
	{
		if (job->ready == 1)
			ft_print_done_job(job);
		else if (job->ready == 2)
			ft_print_job_stop(job);
		else if ((job->ready == 3))
			ft_print_job_term(job);
		job = ft_del_job(job);
	}
}

int		ft_cmd_jobs(char **av)
{
	int 	i;
	char	*tmp;
	int		fl;
	int		start;

	ft_set_shell("?", "0");
	i = 1;
	fl = 0;
	tmp = NULL;
	start = 0;
	while (av && av[i])
	{
		if (av[i][0] == '-' && ft_strchr(av[i], 'l'))
				fl = 1;
		else if (av[i][0] == '-')
			return (ft_jobs_usage(av[i]));
		else
			start = i
		i++;
	}
	return (1);
}
