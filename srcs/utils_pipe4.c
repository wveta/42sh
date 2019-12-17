/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/16 13:16:09 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_set_nopipe_start(t_pipe *p_head)
{
	p_head->cur_cmd->avcmd = ft_all_calc_tst(p_head->cur_cmd->avcmd);
	if (g_calc != 0)
		return (-1);
	if (ft_do_redir(p_head->cur_cmd) != 0)
		return (-1);
	p_head->cur_cmd = ft_local_assig(p_head->cur_cmd);
	if (!(p_head->cur_cmd->avcmd[0]))
	{
		p_head->cur_cmd->locals = ft_put_locals(p_head->cur_cmd->locals);
		p_head->cur_cmd = ft_redir_io_restore(p_head->cur_cmd);
		return (-1);
	}
	p_head->cur_cmd->avcmd = ft_globbing(p_head->cur_cmd->avcmd);
	p_head->cur_cmd->avcmd = ft_cmd_replays(p_head->cur_cmd->avcmd);
	if (g_subs_rc == 1)
		return (-1);
	p_head->cur_cmd->built_in = ft_test_built_in(p_head->cur_cmd->avcmd[0]);
	return (0);
}
