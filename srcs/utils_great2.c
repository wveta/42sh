/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_great2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:25:30 by wveta             #+#    #+#             */
/*   Updated: 2019/12/19 20:25:43 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_str_is_num(char *str, int j)
{
	int i;

	i = 0;
	while (str && i < j && str[i])
	{
		if ((ft_isdigit(str[i]) != 1))
			return (1);
		i++;
	}
	return (0);
}

void	ft_reset_cmd_great(int j, int i, t_cmdlist *cmd)
{
	if (j == 0)
		cmd->avcmd[i][j] = '\0';
	else if (ft_str_is_num(cmd->avcmd[i], j) == 0)
		cmd->avcmd[i][0] = '\0';
	else if (j == 1 && cmd->avcmd[i][j - 1] == '&')
		cmd->avcmd[i][j - 1] = '\0';
}

void	ft_redir_great_close(int out_fd, int direction)
{
	if (out_fd > 2)
		close(out_fd);
	if (g_redir_block == 1)
		close(direction);
}

int		ft_tst_great_fd_loop(t_cmdlist *cmd, int i, t_greatflag *f)
{
	int k;

	if (cmd->avcmd[i + 1])
	{
		k = 0;
		while (cmd->avcmd[i + 1][k])
		{
			if (!(ft_isdigit(cmd->avcmd[i + 1][k])))
			{
				ft_print_msg(" : parse error near :", cmd->avcmd[i + 1]);
				ft_set_shell("?", "1");
				return (-1);
			}
			k++;
		}
		f->out_fd = ft_atoi(cmd->avcmd[i + 1]);
		cmd->avcmd[i + 1][0] = '\0';
/*		k = -1;
		while (cmd->avcmd[i + 1][++k])
		{
			if (!(ft_isdigit(cmd->avcmd[i + 1][k])))
			{
				k = -2;
				break ;
			}
		}
		if (k != -2 && ((f->out_fd = ft_atoi(cmd->avcmd[i + 1]))))
			cmd->avcmd[i + 1][0] = '\0';*/
	}
	return (0);
}
