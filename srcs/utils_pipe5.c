/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/13 11:06:48 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_child_pipe_gojob(t_cmdlist *cur_cmd)
{
	if (g_job == 1)
	{
		if (ft_do_redir(cur_cmd) != 0)
			exit(1);
	}
	cur_cmd->built_in = ft_test_built_in(cur_cmd->avcmd[0]);
	if (cur_cmd->here && ft_get_redir_hd(cur_cmd) != 0)
		exit(1);
	if ((ft_test_built_in(cur_cmd->avcmd[0]) == 1)
		&& (ft_wait_semafor(cur_cmd))
		&& ft_built_in(cur_cmd->avcmd[0],
					cur_cmd->avcmd, cur_cmd->locals) == 1)
		exit(g_built_rc);
}

void	ft_child_pipe_gopipe(t_cmdlist *cur_cmd)
{
	cur_cmd->avcmd = ft_all_calc_tst(cur_cmd->avcmd);
	if (g_calc != 0)
		exit(g_calc);
	if ((cur_cmd->here && ft_get_redir_hd(cur_cmd)) || ft_do_redir(cur_cmd))
		exit(1);
	cur_cmd = ft_local_assig(cur_cmd);
	if (!(cur_cmd->avcmd[0]))
	{
		cur_cmd->locals = ft_put_locals(cur_cmd->locals);
		exit(0);
	}
	cur_cmd->avcmd = ft_cmd_replays(cur_cmd->avcmd);
	cur_cmd->avcmd = ft_globbing(cur_cmd->avcmd);
	cur_cmd->built_in = ft_test_built_in(cur_cmd->avcmd[0]);
	if (cur_cmd->built_in == 0)
	{
		if (!(cur_cmd->find_path = ft_get_file_path(
			cur_cmd->avcmd[0], g_envi->first_list)))
			cur_cmd->find_path = ft_strdup(cur_cmd->avcmd[0]);
	}
	if ((ft_test_built_in(cur_cmd->avcmd[0]) == 1)
		&& (ft_wait_semafor(cur_cmd))
		&& ft_built_in(cur_cmd->avcmd[0],
						cur_cmd->avcmd, cur_cmd->locals) == 1)
		exit(g_built_rc);
}

int		ft_child_pipe_subsh(t_cmdlist *cur_cmd)
{
	while (cur_cmd->avcmd[0][0] && ft_isspace(cur_cmd->avcmd[0][0]))
		ft_strcpy(cur_cmd->avcmd[0], cur_cmd->avcmd[0] + 1);
	if (cur_cmd->avcmd[0][0] == '(' || cur_cmd->avcmd[0][0] == '{')
	{
		g_subshell++;
		if (ft_strlen(cur_cmd->avcmd[0]) < 3)
		{
			ft_print_msg(" : parse error : ", cur_cmd->avcmd[0]);
			exit(1);
		}
		ft_strcpy(cur_cmd->avcmd[0], cur_cmd->avcmd[0] + 1);
		cur_cmd->avcmd[0][ft_strlen(cur_cmd->avcmd[0]) - 1] = '\0';
		g_sub_str = ft_strdup(cur_cmd->avcmd[0]);
		cur_cmd->avcmd[0][0] = '\0';
		ft_child_pipe_varset(cur_cmd);
		ft_pipe_dup_ch_in(cur_cmd);
		ft_pipe_dup_ch_out(cur_cmd);
		if (ft_do_redir(cur_cmd) != 0)
			exit(1);
		g_shell_num++;
		return (1);
	}
	return (0);
}

void	ft_child_pipe_init(int flpi)
{
	ft_sig_set();
	g_check = 1;
	g_subshell++;
	if (g_subs_rc == 1)
		exit(1);
	if ((g_job == 1) || flpi != -777)
	{
		if (g_pgid == 0)
		{
			g_pgid = getpid();
			if (g_job == 0)
				g_pgid = g_parent_pid;
		}
		setpgid(getpid(), g_pgid);
		if (g_job == 0)
			tcsetpgrp(0, g_pgid);
	}
}

void	ft_child_pipe_exec(t_cmdlist *cur_cmd, int flpi)
{
	int		i;

	ft_child_pipe_init(flpi);
	if (ft_child_pipe_subsh(cur_cmd))
		return ;
	else
	{
		ft_pipe_dup_ch_in(cur_cmd);
		ft_pipe_dup_ch_out(cur_cmd);
		sem_post(cur_cmd->bsemafor);
	}
	if (flpi > 0)
		ft_child_pipe_gopipe(cur_cmd);
	else
		ft_child_pipe_gojob(cur_cmd);
	i = ft_test_cmd_file(cur_cmd);
	ft_locals_to_env(cur_cmd->locals);
	sem_wait(cur_cmd->semafor);
	sem_post(cur_cmd->bsemafor);
	if (i == 0)
		execve(cur_cmd->find_path, cur_cmd->avcmd, g_envi->env);
	else
		exit(1);
}