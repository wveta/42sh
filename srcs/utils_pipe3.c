/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/11/12 20:59:07 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipe	*ft_init_p_head(t_cmdlist *first_cmd, t_cmdlist *last_cmd)
{
	t_pipe	*p_head;

	p_head = malloc(sizeof(t_pipe));
	p_head->cur_cmd = first_cmd;
	p_head->first_cmd = first_cmd;
	p_head->last_cmd = last_cmd;
	return (p_head);
}

int		ft_set_fd_pipes(t_pipe *p_head, int fd0[2], int fd1[2])
{
	if (p_head->cur_cmd->nr % 2 == 1)
	{
		if (p_head->cur_cmd != p_head->first_cmd)
			ft_set_cmd_pipe(0, p_head->cur_cmd, fd0, fd1);
		else
			ft_set_cmd_pipe(1, p_head->cur_cmd, fd0, fd1);
		if (p_head->cur_cmd != p_head->last_cmd)
		{
			if (pipe(fd1) < 0)
			{
				ft_print_msg(" : Error in function: ", "PIPE");
				return (-1);
			}
//
		char	*tmp;
		char	*nr;
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\n subshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, p_head->cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " GETPIPE fd1[0] = ");
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, ft_putfnbr(fd1[0], nr));
		tmp = ft_strjoin(tmp, " fd1[1] = ");
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, ft_putfnbr(fd1[1], nr));
		ft_rec_log(tmp);
		free(tmp);
		free(nr);
//			
			ft_set_cmd_pipe(3, p_head->cur_cmd, fd0, fd1);
		}
		else
			ft_set_cmd_pipe(4, p_head->cur_cmd, fd0, fd1);
	}
	else
	{
		if (ft_set_fd_pipes_2(p_head, fd0, fd1) == -1)
			return (-1);
	}
	/*
		char	*tmp;
		char 	*tmp2;
		char	*nr;
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, p_head->cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "p_head->cur_cmd->fd_pipe_in[0] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(p_head->cur_cmd->fd_pipe_in[0], nr));
		ft_rec_log(tmp2);
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "p_head->cur_cmd->fd_pipe_in[1] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(p_head->cur_cmd->fd_pipe_in[1], nr));
		ft_rec_log(tmp2);
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "p_head->cur_cmd->fd_pipe_out[0] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(p_head->cur_cmd->fd_pipe_out[0], nr));
		ft_rec_log(tmp2);
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "p_head->cur_cmd->fd_pipe_out[1] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(p_head->cur_cmd->fd_pipe_out[1], nr));
		ft_rec_log(tmp2);
		free(tmp2);
		free(tmp);
		free(nr);
		
	*/
	return (0);
}

int		ft_set_fd_pipes_2(t_pipe *p_head, int fd0[2], int fd1[2])
{
	if (p_head->cur_cmd != p_head->last_cmd)
	{
		if (pipe(fd0) < 0)
		{
			ft_print_msg(" : Error in function: ", "PIPE");
			return (-1);
		}
//
		char	*tmp;
		char	*nr;
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\n subshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, p_head->cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " GETPIPE fd0[0] = ");
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, ft_putfnbr(fd0[0], nr));
		tmp = ft_strjoin(tmp, " fd0[1] = ");
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, ft_putfnbr(fd0[1], nr));
		ft_rec_log(tmp);
		free(tmp);
		free(nr);
//			
		
		ft_set_cmd_pipe(5, p_head->cur_cmd, fd0, fd1);
	}
	ft_set_cmd_pipe(2, p_head->cur_cmd, fd0, fd1);
	return (0);
}

int		fd_set_nopipe(t_pipe *p_head)
{
	if (ft_do_redir(p_head->cur_cmd) != 0)
		return (-1);
	p_head->cur_cmd = ft_local_assig(p_head->cur_cmd);
	if (!(p_head->cur_cmd->avcmd[0]))
	{
		p_head->cur_cmd->locals = ft_put_locals(p_head->cur_cmd->locals);
		return (-1);
	}
	p_head->cur_cmd->avcmd = ft_cmd_replays(p_head->cur_cmd->avcmd);
	if (g_subs_rc == 1)
		return (-1);
//		
	p_head->cur_cmd->avcmd = ft_get_alias(p_head->cur_cmd->avcmd);
	p_head->cur_cmd->built_in = ft_test_built_in(p_head->cur_cmd->avcmd[0]);
//
	if (p_head->cur_cmd->built_in == 0)
	{
		if (!(p_head->cur_cmd->find_path = ft_get_file_path(
			p_head->cur_cmd->avcmd[0], g_envi->first_list)))
			p_head->cur_cmd->find_path = ft_strdup(p_head->cur_cmd->avcmd[0]);
	}
	else
	{
		if (p_head->cur_cmd->here && ft_get_redir_hd(p_head->cur_cmd) != 0)
			exit(1);
	}
	ft_set_shell("_", p_head->cur_cmd->avcmd[0]);
	if (ft_built_in(p_head->cur_cmd->avcmd[0], p_head->cur_cmd->avcmd, p_head->cur_cmd->locals) == 1)
	{
		p_head->cur_cmd = ft_redir_io_restore(p_head->cur_cmd);
		return (-1);
	}
	return (0);
}

void	ft_parent_wait(t_pipe *p_head, int flpi)
{
	int		status;

	char	*tmp;
	char * nr;

	tmp = ft_strnew(1000);
	nr = ft_strnew(10);
	tmp[0] = '\0';
	tmp = ft_strjoin(tmp, "\n ft_parent_wait  SHELL UID = ");
	nr[0] = '\0';
	nr = ft_putfnbr(getpid(), nr);
	tmp = ft_strjoin(tmp, nr);
	tmp = ft_strjoin(tmp, " g_semafor = ");
	nr[0] = '\0';
	nr = ft_putfnbr((int)g_semafor, nr);
	tmp = ft_strjoin(tmp, nr);
	ft_rec_log(tmp);
	free(tmp);
	free(nr);
	
	if (g_semafor)
	{
		tmp = ft_strnew(1000);
		nr = ft_strnew(10);
		tmp[0] = '\0';
		tmp = ft_strjoin(tmp, "\n Subshell  WAIT ");
		tmp = ft_strjoin(tmp, " SHELL UID = ");
		nr[0] = '\0';
		nr = ft_putfnbr(getpid(), nr);
		tmp = ft_strjoin(tmp, nr);
		tmp = ft_strjoin(tmp, " g_semafor = ");
		nr[0] = '\0';
		nr = ft_putfnbr((int)g_semafor, nr);
		tmp = ft_strjoin(tmp, nr);
		ft_rec_log(tmp);
	
		sem_wait(g_semafor);

		tmp[0] = '\0';
		tmp = ft_strjoin(tmp, "\n Subshell GO ");
		tmp = ft_strjoin(tmp, " SELL UID = ");
		nr[0] = '\0';
		nr = ft_putfnbr(getpid(), nr);
		tmp = ft_strjoin(tmp, nr);
		ft_rec_log(tmp);	
		free(tmp);
		free(nr);	
	}
	
	ft_add_semafor(p_head);
	
	if (g_bsemafor)
	{
		tmp = ft_strnew(1000);
		nr = ft_strnew(10);
		tmp[0] = '\0';
		tmp = ft_strjoin(tmp, "\n Subshell  post parent ");
		tmp = ft_strjoin(tmp, " SHELL UID = ");
		nr[0] = '\0';
		nr = ft_putfnbr(getpid(), nr);
		tmp = ft_strjoin(tmp, nr);
		tmp = ft_strjoin(tmp, " g_bsemafor = ");
		nr[0] = '\0';
		nr = ft_putfnbr((int)g_bsemafor, nr);
		tmp = ft_strjoin(tmp, nr);
		ft_rec_log(tmp);
		free(tmp);
		free(nr);
		
		sem_post(g_bsemafor);
	}
	
	ft_sig_set();
	if (g_job == 0 && flpi == 0)
	{
		while (p_head->first_cmd->pid != 0)
			status = 0;
		status = p_head->first_cmd->status;
		ft_set_cmd_exit_status(status);
		p_head->first_cmd = ft_redir_io_restore(p_head->first_cmd);
		return ;
	}
	ft_pipe_wait_ch_fin(p_head->cur_cmd, p_head->first_cmd, p_head->last_cmd, flpi);
}
