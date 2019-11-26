/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_in_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/26 12:34:17 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_restore_io(void)
{
	if (g_std_in > -1)
		dup2(g_std_in, STDIN_FILENO);
	if (g_std_out > -1)
		dup2(g_std_out, STDOUT_FILENO);
	if (g_stderr > -1)
		dup2(g_stderr, STDERR_FILENO);
}
void	ft_job_fg(t_job *j)
{
	t_proc			*p;
	struct termios	tmodes;

	
	tcgetattr(0, &tmodes);
	tcsetpgrp(0, j->pgid);

	p = j->first_proc;
	kill(-j->pgid, SIGCONT);
	while (p)
	{
		if (p->completed != 1)
		{
			p->stopped = 0;
		}
//		if (kill(p->pid, SIGCONT) < 0)
//    		ft_print_msg(": SIGCONT error ", " ");
		p = p->next;
	}

	p = j->first_proc;
	while (p)
	{
		if (p->stopped == 1)
			break;
		else if (p->completed == 1 && (!(p->next)))
		{
			ft_set_cmd_exit_status(p->status);
			break ;
		}
		if (p->next)
			p = p->next;
		else
			p = j->first_proc;		
	}
	tcsetpgrp(0, getpid());
	tcsetattr(0, TCSADRAIN, &tmodes);
}

int		ft_cmd_fg(char **av)
{
	t_job	*j;
	int 	i;
	char	*num;

	j = g_job_first;
	i = 0;
	while(j)
	{
		num = ft_num_to_str(j->num);	
		if (((av && av[1] && ft_strcmp(av[1], num) == 0) ||
			((!(av[1]) && j->flag == '+'))) && ((i = 1)))
			ft_job_fg(j);
		free(num);
		if (i == 1)
			break ;
		j = j->next;
	}
	if (i == 0)
	{
		if (av[1])
			ft_print_msg(": jobs: no such job: ", av[1]);
		else
			ft_print_msg(": jobs: current: no such job", " ");
		ft_set_shell("?", "1");
	}
	else
		ft_set_shell("?", "0");		
	return (1);
}

void	ft_set_job_cont(t_job *j)
{
	t_proc *p;

	if (j)
	{
		if (j->stat_job)
			free(j->stat_job);
		j->stat_job = ft_strdup("Running           ");
		p = j->first_proc;
		while (p)
		{
			if (p->completed != 1 && p->stopped == 1)
				p->stopped = 0;
			p = p->next;
		}
	}
}
