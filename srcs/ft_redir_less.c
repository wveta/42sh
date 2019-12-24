/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_less.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/24 22:35:04 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_fd_by_n(int i, t_cmdlist *cmd, char *ind)
{
	char		*file_redir;
	int			len;

	if (((int)ft_strlen(cmd->avcmd[i]) >= ind - cmd->avcmd[i] + 2) &&
		(cmd->avcmd[i][ind - cmd->avcmd[i] + 2] == '-') &&
		(file_redir = ft_strdup("/dev/null")))
		g_redir_block = 1;
	else if ((int)ft_strlen(cmd->avcmd[i]) > ind - cmd->avcmd[i] + 1)
	{
		file_redir = ft_strdup(ind + 1);
		file_redir = ft_repl_tilda(file_redir, ft_strlen(file_redir));
	}
	else if (cmd->avcmd[i + 1] && (file_redir = ft_strdup(cmd->avcmd[i + 1])))
		cmd->avcmd[i + 1][0] = '\0';
	else
		return (ft_print_msg(" : syntax error in command ", ""));
	cmd->avcmd[i][ind - cmd->avcmd[i]] = '\0';
	file_redir = del_ekran(file_redir);
	if (ft_test_file_mame(file_redir) != 0 && ft_free_ret(file_redir))
		return (-1);
	file_redir = ft_calc_full_path(file_redir);
	if ((len = open(file_redir, O_RDONLY, 0644)) == -1)
		ft_print_msg(" : Error open file ", file_redir);
	free(file_redir);
	return (len);
}

int		ft_get_fd_bynum(int i, int j, t_cmdlist *cmd)
{
	int			in_fd;

	in_fd = -1;
	if (cmd->avcmd[i][j + 1] == '&')
	{
		if ((int)ft_strlen(cmd->avcmd[i]) > j + 2)
		{
			if (ft_less_w0(&in_fd, i, j, cmd) == -2)
				return (-2);
		}
		else if (cmd->avcmd[i + 1])
		{
			if (ft_less_w1(&in_fd, i, cmd) == -2)
				return (-2);
		}
		else
		{
			ft_print_msg(" : parse error near :", cmd->avcmd[i] + j + 1);
			ft_set_shell("?", "1");
			return (-2);
		}
	}
	return (in_fd);
}

int		ft_get_next_num(char *s)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
		{
			ft_print_msg(" : parse error near :", s + i);
			ft_set_shell("?", "1");
			return (-1);
		}
		i++;
	}
	ret = ft_atoi(s);
	return (ret);
}

int		ft_get_prev_num(char *s, int k)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (i < k && s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (-1);
		i++;
	}
	ret = ft_atoi(s);
	return (ret);
}

int		ft_redir_less(t_cmdlist *cmd, int i)
{
	int			j;
	char		*ind;
	int			in_fd;

	j = 0;
	while (cmd->avcmd[i] && (ind = (ft_strchr(cmd->avcmd[i] + j, '<'))))
	{
		j = ind - cmd->avcmd[i];
		if (ft_check_ekran(cmd->avcmd[i], j) == 0 && (in_fd = -1))
		{
			if (ft_strncmp(ind, LESS, 1) == 0 &&
				((int)ft_strlen(cmd->avcmd[i]) - 1 == j || (cmd->avcmd[i][j + 1]
				!= '<' && cmd->avcmd[i][j + 1] != '>')))
			{
				if ((in_fd = ft_get_fd_bynum(i, j, cmd)) == -2)
					return (-1);
				if (in_fd == -1 && ((in_fd = ft_get_fd_by_n(i, cmd, ind)) < 0))
					return (-1);
				return (ft_fd_dup_close(in_fd, i, j, cmd));
			}
			return (0);
		}
		j++;
	}
	return (0);
}
