/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/11/15 15:29:20 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parent_close_pipe(int code, int fd0[2], int fd1[2])
{
	//
		char	*tmp;
		char 	*tmp2;
		char	*nr;
	if (code == 0)
	{
		if (fd0[0] != -1)
		{
			close(fd0[0]);
		
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " SHELL ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE fd0[0] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(fd0[0], nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);
		}
		if (fd0[1] != -1)
		{
			close(fd0[1]);
			
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " SHELL ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE fd0[1] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(fd0[1], nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);		
		
		}
		ft_init_arr_fd(0, fd0, fd1);
	}
	else
	{
		if (fd1[0] != -1)
		{
			close(fd1[0]);
			
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " SHELL ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE fd1[0] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(fd1[0], nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);	
		}
		if (fd1[1] != -1)
		{
			close(fd1[1]);

		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " SHELL ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE fd1[1] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(fd1[1], nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);	
		}
		ft_init_arr_fd(1, fd0, fd1);
	}
}

void	ft_parent_pipe_next(t_cmdlist *cur_cmd, int fd0[2],
		int fd1[2], int flpi)
{
//13.11
//		char	*tmp;
//		char 	*tmp2;
//		char	*nr;
//13.11
	
	if (flpi > 0 && cur_cmd->nr == 1)
		return ;
	if (flpi > 0 && cur_cmd->nr % 2 == 1)
		ft_parent_close_pipe(0, fd0, fd1);
	else if (flpi > 0 && cur_cmd->nr % 2 != 1)
		ft_parent_close_pipe(1, fd0, fd1);


/*13.11
	if (g_subshell > 0)
	{
		if (cur_cmd->nr == 1)
		{
			if (g_subsh_in0 != -1)
			{
				close(g_subsh_in0);
				
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " SHELL ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE g_subsh_in0 = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_in0, nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);
		
				g_subsh_in0 = -1;
			}
			if (g_subsh_in1 != -1)
			{
				close(g_subsh_in1);
				
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " SHELL ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE g_subsh_in1 = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_in1, nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);
				g_subsh_in1 = -1;
			}
		}
		if (!(cur_cmd->next))
		{
			if (g_subsh_out0 != -1)
			{
				close(g_subsh_out0);
				
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE g_subsh_out0 = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_out0, nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);
				g_subsh_out0 = -1;
			}
			if (g_subsh_out1 != -1)
			{
				close(g_subsh_out1);
				
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, " CLOSE g_subsh_out1 = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_out1, nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);

				g_subsh_out1 = -1;
			}

		}
	}
*/
}

void	ft_child_pipe_exec(t_cmdlist *cur_cmd, int flpi)
{
	int		i;
	char	*tmp;

//
	char * nr;
	
	tmp = ft_strnew(1000);
	nr = ft_strnew(10);
	tmp[0] = '\0';
	tmp = ft_strjoin(tmp, "\n AFTER FORK START PROC \n");
	i = -1;
	while (cur_cmd->avcmd[++i])
	{
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	tmp = ft_strjoin(tmp, "\nUID = ");
	nr[0] = '\0';
	nr = ft_putfnbr(getpid(), nr);

	ft_rec_log(tmp);
	free (tmp);
	free(nr);
//


	ft_sig_set();
	g_check = 1;
	if (g_subs_rc == 1)
		exit(1);
	if (g_job == 1 || flpi > 0)
	{
		if (g_pgid == 0)
		{
			g_pgid = getpid();
			if (g_job == 0)
				g_pgid = g_parent_pid;
		}
		setpgid(getpid(), g_pgid);
		if (g_job == 0)
			tcsetpgrp(0,  g_pgid);
	}
	signal(SIGINT, ft_signal_child);
	signal(SIGQUIT, ft_signal_child);
	signal(SIGTSTP, ft_signal_child);
	if (cur_cmd->avcmd[0][0] == '(' || cur_cmd->avcmd[0][0] == '{')
	{
		g_subshell++;

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
	tmp = ft_strnew(1000);
	nr = ft_strnew(10);
	tmp[0] = '\0';
	tmp = ft_strjoin(tmp, "\n AFTER REDIRECT \n");
	i = -1;
	while (cur_cmd->avcmd[++i])
	{
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	tmp = ft_strjoin(tmp, "\nUID = ");
	nr[0] = '\0';
	nr = ft_putfnbr(getpid(), nr);

	ft_rec_log(tmp);
	free (tmp);
	free(nr);
	
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
		cur_cmd->avcmd = ft_cmd_replays(cur_cmd->avcmd);
		cur_cmd = ft_local_assig(cur_cmd);
		if (!(cur_cmd->avcmd[0]))
		{
			cur_cmd->locals = ft_put_locals(cur_cmd->locals);
			exit(0);
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
		if ((ft_test_built_in(cur_cmd->avcmd[0]) == 1) && (ft_wait_semafor(cur_cmd))
			&& ft_built_in(cur_cmd->avcmd[0], cur_cmd->avcmd, cur_cmd->locals) == 1)
			exit(g_built_rc);
	}
	else
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
	/*	if ((cur_cmd->nr == 1) && g_subshell > 0)
		{
			tmp = ttyname(STDERR_FILENO);
			i = open(tmp, O_RDONLY , S_IRUSR | S_IWUSR);
			if (i != -1 && (dup2(i, STDIN_FILENO) == -1))
				ft_print_msg(": error DUP2 STDIN: ", "subshell");
		}*/

//
	char	*tmp;
	char * nr;
	
	tmp = ft_strnew(1000);
	nr = ft_strnew(10);
	tmp[0] = '\0';
	tmp = ft_strjoin(tmp, "\n Process WAIT ");
	tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
	tmp = ft_strjoin(tmp, " UID = ");
	nr[0] = '\0';
	nr = ft_putfnbr(getpid(), nr);
	tmp = ft_strjoin(tmp, nr);
	tmp = ft_strjoin(tmp, " semafor = ");
	nr[0] = '\0';
	nr = ft_putfnbr((int)cur_cmd->semafor, nr);
	tmp = ft_strjoin(tmp, nr);
	ft_rec_log(tmp);
		
		sem_wait(cur_cmd->semafor);
		sem_post(cur_cmd->bsemafor);

	tmp[0] = '\0';
	tmp = ft_strjoin(tmp, "\n Process GO ");
	tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
	tmp = ft_strjoin(tmp, " UID = ");
	tmp = ft_strjoin(tmp, nr);
	ft_rec_log(tmp);
		
		execve(cur_cmd->find_path, cur_cmd->avcmd, g_envi->env);
	}
	exit (1);
}

void	ft_pipe_wait_ch_fin(t_cmdlist *cur_cmd, t_cmdlist *first_cmd, t_cmdlist *last_cmd, int flpi)
{
	int			status;
	int			j;
	int			q;
	char		*tmp;
	char		*nr;
	
	if (g_job == 0 && flpi > 0)
	{
		while (1)
		{	
			cur_cmd = first_cmd;
			q = 0;
			while (cur_cmd)
			{
				if (cur_cmd->pid != 0)
				{
					q++;
					status = 0;
					if ((j = waitpid(cur_cmd->pid, &status, WNOHANG | WUNTRACED
					)) == cur_cmd->pid)
					{
						if ((!(cur_cmd->next)))
							ft_set_cmd_exit_status(status);
//

						tmp = ft_strnew(1000);
						tmp[0] = '\0';
						nr = ft_strnew(1000);
						nr[0] = '\0';
						tmp = ft_strjoin(tmp, "\n subshell = ");
						tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
						tmp = ft_strjoin(tmp, " ");
						tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
						tmp = ft_strjoin(tmp, " RC = ");
						tmp = ft_strjoin(tmp, ft_putfnbr(status, nr));
						ft_rec_log(tmp);
						free(tmp);
						free(nr);
//
						cur_cmd->pid = 0;	
					}
				}
				cur_cmd = cur_cmd->next;
/*				if (last_cmd->pid == 0)
				{
					if (flpi == 0)
						first_cmd = ft_redir_io_restore(first_cmd);
					return ;
				}*/
			}
			if (q == 0)
			{
				(void)last_cmd;
				if (flpi == 0)
					first_cmd = ft_redir_io_restore(first_cmd);
				return ;
			}
		}

	}
	else
	{
		first_cmd = ft_redir_io_restore(first_cmd);
	}
}
