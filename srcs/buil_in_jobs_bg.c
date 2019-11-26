/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_in_jobs_bg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/26 19:41:23 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_to_job(int status)
{
	t_job		*cur_job;
	t_cmdlist	*cmd;
	pid_t 		my_pgid;

	cur_job = NULL;
	my_pgid = 0;
	if (g_pipe && (g_pipe->first_cmd->built_in == 0 || 
	g_pipe->first_cmd != g_pipe->last_cmd))
	{
		cmd = g_pipe->first_cmd;
		while(cmd)
		{
			if (my_pgid == 0)
				my_pgid = cmd->pid_z;
			if (cmd->nr == 1)
			{
				cur_job = ft_new_job(cmd);
				ft_set_job_status(cur_job, 2, status);
				if (!(g_job_first))
				{
					g_job_first = cur_job;
					cur_job->num = 1;
				}
				else
					ft_insert_job(cur_job);
				cur_job->orig_cmd = ft_strncpy(ft_strnew((size_t)
				(g_job_end + 1)), g_job_start, g_job_end);
				ft_set_job_plus();
				ft_print_start_job(cur_job);
			}
			ft_add_proc(cmd);
			setpgid(cmd->pid, my_pgid);
			tcsetpgrp(cmd->pid_z,  my_pgid);
			cmd->pid = 0;
			cmd = cmd->next;
		}
	}
}

int		ft_cmd_bg(char **av)
{
	t_job	*j;
	int 	i;
	char	*num;
	int		l;

	if ((!(av[1])))
	{
		j = g_job_first;
		while(j)
		{
			if (j->flag == '+')
			{
//				kill (-j->pgid, SIGCONT);
				kill (j->pgid, SIGCONT);
				break ;
			}
			j = j->next;
		}
	}
	else
	{
		l = 0;
		while (av && av[++l])
		{
			i = 0;
			j = g_job_first;
			while(j)
			{
				num = ft_num_to_str(j->num);
				if (ft_strcmp(av[l], num) == 0 && ((i = 1)))
//					kill (-j->pgid, SIGCONT);
					kill (j->pgid, SIGCONT);
				free(num);
				j = j->next;
			}
			if (i == 0)
			{
				if (av[l])
					ft_print_msg(": jobs: no such job: ", av[l]);
				ft_set_shell("?", "1");
			}
			else
				ft_set_shell("?", "0");
		}
	}	
	return (1);
}

char	*ft_get_str_cmd(char **s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	while(s && s[i])
	{
		tmp = ft_strfjoin(tmp, s[i]);
		tmp = ft_strfjoin(tmp, " ");
		i++;
	}
	return (tmp);
}

void	ft_test_tstp(pid_t pid2, int status)
{
	t_job		*job;
	t_proc		*proc;
	t_job		*job_new;
	pid_t		pid;

	job = g_job_first;
	job_new = NULL;
	pid = pid2;
	if (pid2 == 0 && g_pipe)
		pid = g_pipe->first_cmd->pid_z;
	while(job)
	{
		if (pid == job->pgid)
			return ;
		proc = job->first_proc;
		while(proc)
		{
			if (pid == proc->pid)
				return ;
			proc = proc->next;
		}
		job = job->next;
	}
	ft_cmd_to_job(status);
}
