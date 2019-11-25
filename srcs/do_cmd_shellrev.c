/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd_shellrev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/25 18:07:46 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_test_built_in(char *path)
{
	if (path && ft_strcmp(path, "exit") == 0)
		return (1);
	else if (path && g_envi->env && ft_strcmp(path, "set") == 0)
		return (1);
	else if (path && ft_strcmp(path, "cd") == 0)
		return (1);
	else if (path && ft_strcmp(path, "export") == 0)
		return (1);
	else if (path && ft_strcmp(path, "unset") == 0)
		return (1);
	else if (path && ft_strcmp(path, "echo") == 0)
		return (1);
	else if (path && ft_strcmp(path, "type") == 0)
		return (1);
	else if (path && ft_strcmp(path, "printenv") == 0)
		return (1);
	else if (path && ft_strcmp(path, "hash") == 0)
		return (1);
	else if (path && ft_strcmp(path, "jobs") == 0)
		return (1);
	else if (path && ft_strcmp(path, "fg") == 0)
		return (1);
	else if (path && ft_strcmp(path, "bg") == 0)
		return (1);
	else if (path && ft_strcmp(path, "kill") == 0)
		return (1);
	else if (path && ft_strcmp(path, "alias") == 0)
		return (1);
	else if (path && ft_strcmp(path, "unalias") == 0)
		return (1);
	else if (path && ft_strcmp(path, "test") == 0)
		return (1);
	return (0);
}

t_cmdlist	*ft_free_cmd_list(t_cmdlist *first)
{
	t_cmdlist	*cur;
	t_cmdlist	*tmp;

	cur = first;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->avcmd)
			ft_free_char_matr(tmp->avcmd);
		if (tmp->built_in != 1 && tmp->find_path)
			free(tmp->find_path);
		if (tmp->here)
			free(tmp->here);
		ft_del_semafor(tmp);
		free(tmp);
	}
	return (NULL);
}

void		ft_do_cmd_list(t_pipe *p_head, int flpi)
{
	int				fd0[2];
	int				fd1[2];
	struct termios	tmodes;

	ft_init_arr_fd(2, fd0, fd1);
	g_pipe = p_head;
	g_flpi = flpi;
	p_head->cur_cmd = p_head->first_cmd;
	p_head->cur_cmd->avcmd = ft_isnot(p_head->cur_cmd->avcmd);
	if (g_subshell == 0)
		g_pgid = 0;
	tcgetattr(0, &tmodes);
	while (p_head->cur_cmd)
	{
		p_head->cur_cmd->avcmd = ft_globbing(p_head->cur_cmd->avcmd);
		if (ft_get_heretext(p_head->cur_cmd) == -1)
			return;
		if (flpi > 0 && ((ft_set_fd_pipes(p_head, fd0, fd1) == -1)))
			return ;
		else if (flpi < 1 && g_job != 1 &&
		(fd_set_nopipe(p_head) == -1))
			return ;
		if (ft_fork(p_head) == -1)
			return ;
		else if (p_head->cur_cmd->pid == 0)
		{
			ft_child_pipe_exec(p_head->cur_cmd, flpi);
			if (g_sub_str && g_subshell > 0)
				return ;
		}
		else if (p_head->cur_cmd->pid > 0)
		{
			ft_sig_set();
//			if (g_job == 1 || flpi > 0)
//			{
				if (g_pgid == 0)
					g_pgid = p_head->cur_cmd->pid;
				setpgid(p_head->cur_cmd->pid, g_pgid);
				if (g_job == 0)
					tcsetpgrp(0,  g_pgid);
//			}
			ft_if_job(p_head->cur_cmd);
			ft_parent_pipe_next(p_head->cur_cmd, fd0, fd1, flpi);
			p_head->cur_cmd = p_head->cur_cmd->next;
		}
	}
	ft_parent_wait(p_head, flpi);
	tcsetattr(0, TCSADRAIN, &tmodes);
	g_pipe = NULL;
}

void		ft_do_cmd_shell(char **av, int start, int flagpipe)
{
	int			nextpipe;
	t_pipe		*p_head;
	int			fl;

	p_head = ft_init_p_head(NULL, NULL);
	while ((start == 0 || av[start - 1]) && av[start])
	{
		fl = 0;
		if (!(p_head->cur_cmd = malloc(sizeof(t_cmdlist))))
			break ;
		ft_init_curcmd(p_head->cur_cmd);
		ft_set_cmd(p_head);
		if (((nextpipe = ft_get_count_in_pipe(av, start)) < 1 && flagpipe > 0)
			|| (ft_test_cmd_pipe(av, start, p_head) == -1))
			break ;
		fl = 1;
		if (flagpipe > 0)
			start = start + nextpipe + 1;
		else
			break ;
			
	}
	if (fl == 1)
		ft_do_cmd_list(p_head, flagpipe);	
	p_head->first_cmd = ft_free_cmd_list(p_head->first_cmd);
	free(p_head);

}
