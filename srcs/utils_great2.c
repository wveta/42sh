/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_great2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:25:30 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 22:34:29 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_reset_cmd_great(int j, int i, t_cmdlist *cmd)
{
	if (j == 0)
		cmd->avcmd[i][j] = '\0';
	else if ((ft_isdigit(cmd->avcmd[i][j - 1]) == 1) || (
		j == 1 && cmd->avcmd[i][j - 1] == '&'))
		cmd->avcmd[i][j - 1] = '\0';
}

void	ft_redir_great_close(int out_fd, int direction)
{
	if (out_fd > 2)
		close(out_fd);
	if (g_redir_block == 1)
		close(direction);
}

void	ft_tst_great_fd_loop(t_cmdlist *cmd, int i, t_greatflag *f)
{
	int k;

	if (cmd->avcmd[i + 1])
	{
		k = -1;
		while (cmd->avcmd[i + 1][++k])
		{
			if (!(ft_isdigit(cmd->avcmd[i + 1][k])))
			{
				k = -2;
				break ;
			}
		}
		if (k != -2 && ((f->out_fd = ft_atoi(cmd->avcmd[i + 1]))))
			cmd->avcmd[i + 1][0] = '\0';
	}
}
