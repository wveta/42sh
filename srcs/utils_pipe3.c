/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/09/06 14:56:39 by wveta            ###   ########.fr       */
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
		ft_set_cmd_pipe(5, p_head->cur_cmd, fd0, fd1);
	}
	ft_set_cmd_pipe(2, p_head->cur_cmd, fd0, fd1);
	return (0);
}

int		fd_set_nopipe(t_pipe *p_head)
{
	if (ft_do_redir(p_head->cur_cmd) != 0)
		return (-1);
	if (ft_built_in(p_head->cur_cmd->avcmd[0], p_head->cur_cmd->avcmd) == 1)
	{
		p_head->cur_cmd = ft_redir_io_restore(p_head->cur_cmd);
		return (-1);
	}
	return (0);
}

void	ft_parent_wait(t_pipe *p_head, int flpi, t_cmdlist *first_cmd)
{
	int		status;
	int 	i;

	if (flpi == 0)
	{
		waitpid(p_head->first_cmd->pid, &status, 0);
		if (WIFEXITED(status))
		{
			if ((i = WEXITSTATUS(status)) != 0)
				ft_set_shell("?", "1");
			else
				ft_set_shell("?", "0");			
		}
		first_cmd = ft_redir_io_restore(first_cmd);
		return ;
	}
	ft_pipe_wait_ch_fin(p_head->cur_cmd, p_head->first_cmd, p_head->last_cmd);
}
