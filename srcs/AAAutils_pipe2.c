/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAAutils_pipe2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 22:42:40 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_sig2(int f1, int f2)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 10);
	tmp[0] = '\0';
	if (tmp)
	{
		if (f1)
			ft_print_msg(" : f1  :", ft_putfnbr(f1, tmp));
		tmp[0] = '\0';
		if (f2)
			ft_print_msg(" : f2  :", ft_putfnbr(f2, tmp));
	}
	free(tmp);
}


void	ft_parent_close_pipe(int code, int fd0[2], int fd1[2])
{
	if (code == 0)
	{
		if (fd0[0] != -1)
			close(fd0[0]);
		if (fd0[1] != -1)
			close(fd0[1]);
		ft_init_arr_fd(0, fd0, fd1);
	}
	else
	{
		if (fd1[0] != -1)
			close(fd1[0]);
		if (fd1[1] != -1)
			close(fd1[1]);
		ft_init_arr_fd(1, fd0, fd1);
	}
}

void	ft_parent_pipe_next(t_cmdlist *cur_cmd, int fd0[2],
		int fd1[2], int flpi)
{
	if (flpi > 0 && cur_cmd->nr == 1)
		return ;
	if (flpi > 0 && cur_cmd->nr % 2 == 1)
		ft_parent_close_pipe(0, fd0, fd1);
	else if (flpi > 0 && cur_cmd->nr % 2 != 1)
		ft_parent_close_pipe(1, fd0, fd1);
}

void	ft_child_pipe_exec(t_cmdlist *cur_cmd, int flpi)
{
	int		i;

	ft_sig_set();
	g_check = 1;
	g_subshell++;
	if (g_subs_rc == 1)
		exit(1);
		if (g_pgid == 0)
		{
			g_pgid = getpid();
		}
		setpgid(getpid(), g_pgid);
		if (g_job == 0)
			tcsetpgrp(0,  g_pgid);
	while (cur_cmd->avcmd[0][0] && ft_isspace(cur_cmd->avcmd[0][0]))
		ft_strcpy(cur_cmd->avcmd[0], cur_cmd->avcmd[0] + 1);
	if (cur_cmd->avcmd[0][0] == '(' || cur_cmd->avcmd[0][0] == '{')
	{
//		g_subshell++;
		if (ft_strlen(cur_cmd->avcmd[0]) < 3)
		{
			ft_print_msg(" : parse error : ", cur_cmd->avcmd[0]);
			exit(1);
		}
		ft_strcpy(cur_cmd->avcmd[0], cur_cmd->avcmd[0] + 1);
		cur_cmd->avcmd[0][ft_strlen(cur_cmd->avcmd[0]) - 1] = '\0';
		g_sub_str = ft_strdup(cur_cmd->avcmd[0]);
		cur_cmd->avcmd[0][0] = '\0';
			g_semafor = cur_cmd->semafor;
			g_bsemafor = cur_cmd->bsemafor;
			g_sem_name = cur_cmd->sem_name;
			g_bsem_name = cur_cmd->bsem_name;
			cur_cmd->semafor = NULL;
			cur_cmd->bsemafor = NULL;
			cur_cmd->sem_name = NULL;
			cur_cmd->sem_name = NULL;
			ft_pipe_dup_ch_in(cur_cmd);
			ft_pipe_dup_ch_out(cur_cmd);
			if (ft_do_redir(cur_cmd) != 0)
				exit(1);
		return;
	}
	else
	{
		ft_pipe_dup_ch_in(cur_cmd);
		ft_pipe_dup_ch_out(cur_cmd);
///		
		sem_post(cur_cmd->bsemafor);
	}
	if (flpi > 0)
	{
		
		if (cur_cmd->here && ft_get_redir_hd(cur_cmd) != 0)
			exit(1);
		if (ft_do_redir(cur_cmd) != 0)
			exit(1);
/**/	
		cur_cmd = ft_local_assig(cur_cmd);
		if (!(cur_cmd->avcmd[0]))
		{
			cur_cmd->locals = ft_put_locals(cur_cmd->locals);
			exit(0);
		}
//
		cur_cmd->avcmd = ft_all_calc_tst(cur_cmd->avcmd);
		if (g_calc != 0)
			exit(g_calc);
		cur_cmd->avcmd = ft_cmd_replays(cur_cmd->avcmd);
		cur_cmd->avcmd = ft_get_alias(cur_cmd->avcmd);
		cur_cmd->built_in = ft_test_built_in(cur_cmd->avcmd[0]);
		
	
//
		if (cur_cmd->built_in == 0)
		{	
			if (!(cur_cmd->find_path = ft_get_file_path(
				cur_cmd->avcmd[0], g_envi->first_list)))
				cur_cmd->find_path = ft_strdup(cur_cmd->avcmd[0]);
		}
		if ((ft_test_built_in(cur_cmd->avcmd[0]) == 1) && (ft_wait_semafor(cur_cmd))
			&& ft_built_in(cur_cmd->avcmd[0], cur_cmd->avcmd, cur_cmd->locals) == 1)
			exit(g_built_rc);
	}
	else if (g_job == 1)
	{
		if (g_job == 1)
		{
			if (ft_do_redir(cur_cmd) != 0)
				exit(1);
		}	
//
		cur_cmd->avcmd = ft_get_alias(cur_cmd->avcmd);
		cur_cmd->built_in = ft_test_built_in(cur_cmd->avcmd[0]);
//
		if (cur_cmd->built_in == 0)
		{
			if (!(cur_cmd->find_path = ft_get_file_path(
				cur_cmd->avcmd[0], g_envi->first_list)))
				cur_cmd->find_path = ft_strdup(cur_cmd->avcmd[0]);
		}
		if (cur_cmd->here && ft_get_redir_hd(cur_cmd) != 0)
			exit(1);
//
		if ((ft_test_built_in(cur_cmd->avcmd[0]) == 1) && (ft_wait_semafor(cur_cmd))
			&& ft_built_in(cur_cmd->avcmd[0], cur_cmd->avcmd, cur_cmd->locals) == 1)
			exit(g_built_rc);
//
	}
	if ((i = ft_test_cmd_file(cur_cmd)) == 0)
	{
		ft_locals_to_env(cur_cmd->locals);
		sem_wait(cur_cmd->semafor);
		sem_post(cur_cmd->bsemafor);
		execve(cur_cmd->find_path, cur_cmd->avcmd, g_envi->env);
	}
	exit (1);
}

void	ft_pipe_wait_ch_fin(t_cmdlist *cur_cmd, t_cmdlist *first_cmd, t_cmdlist *last_cmd, int flpi)
{
	int			status;
	int			j;
	int			q;
	
	if (g_job == 0 && flpi > 0)
	{
		j = 0;
		while (1)
		{	
			cur_cmd = first_cmd;
			q = 0;
			
			while (cur_cmd)
			{
				if (cur_cmd->pid != 0)
				{
					q++;
//					ft_print_sig2(cur_cmd->pid, q);
//					status = 0;
//					
//						if ((j = waitpid(cur_cmd->pid, &status, WNOHANG | WUNTRACED
//						)) == cur_cmd->pid)
//						{
//							ft_print_sig2(q, cur_cmd->pid);
//							if (0 == kill(cur_cmd->pid_z, 0))
//							{
//								ft_print_sig2(q, 777);
//								cur_cmd->pid = 0;
//								q--;
/*								
							ft_print_sig(status);
							if ((WIFEXITED(status)))
								cur_cmd->pid = 0;
							else if (WIFSTOPPED(status) && 18 == WSTOPSIG(status))
							{
								cur_cmd->pid = 0;
								if (g_subshell > 0)
									kill (g_parent_pid, SIGTSTP);
							}
							else if (WIFSTOPPED(status) && 22 == WSTOPSIG(status))
								kill(-cur_cmd->pid, SIGCONT);
							else if (WIFSIGNALED(status))
								cur_cmd->pid = 0;	*/				
								if  (cur_cmd->pid == 0 && j == 0)
								{
									ft_set_cmd_exit_status(cur_cmd->status);
									if (!((WIFEXITED(status)) && WEXITSTATUS(status) == 0))
										j = cur_cmd->status;
								}
//							}
//						}
				}
				else if  (j == 0)
				{
					ft_set_cmd_exit_status(cur_cmd->status);
					if (!((WIFEXITED(status)) && WEXITSTATUS(status) == 0))
					j = cur_cmd->status;
				}
				cur_cmd = cur_cmd->next;
			}
			
			if (q == 0)
			{
				(void)last_cmd;
//				if (flpi == 0)
					first_cmd = ft_redir_io_restore(first_cmd);
				return ;
			}
		}
	}
	else
		first_cmd = ft_redir_io_restore(first_cmd);
}
