/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:00:14 by wveta             #+#    #+#             */
/*   Updated: 2019/12/10 16:27:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_set_var_ex_lst(int *j, int *l)
{
	char	*ret;

	ret = ft_get_env("PATH");
	*j = 0;
	*l = 0;
	return (ret);
}

int		ft_test_cmd_file(t_cmdlist *cur_cmd)
{
	struct stat	buff;
	int			k;

	if (!(cur_cmd->find_path))
		return (-1);
	if (ft_check_file(cur_cmd->find_path, X_OK) != 0)
		return (-1);
	if ((k = stat(cur_cmd->find_path, &buff)) == 0 &&
		(buff.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_print_msg(" : is a directory: ", cur_cmd->find_path);
		ft_set_shell("?", "1");
		return (-1);
	}
	return (0);
}

void	ft_add_built_to_list(int j)
{
	g_cmd->cmd_list[j] = ft_strdup("exit");
	g_cmd->cmd_list[j + 1] = ft_strdup("export");
	g_cmd->cmd_list[j + 2] = ft_strdup("unset");
	g_cmd->cmd_list[j + 3] = ft_strdup("set");
	g_cmd->cmd_list[j + 4] = ft_strdup("cd");
	g_cmd->cmd_list[j + 5] = ft_strdup("type");
	g_cmd->cmd_list[j + 6] = ft_strdup("printenv");
	g_cmd->cmd_list[j + 7] = ft_strdup("hash");
	g_cmd->cmd_list[j + 8] = ft_strdup("jobs");
	g_cmd->cmd_list[j + 9] = ft_strdup("fg");
	g_cmd->cmd_list[j + 10] = ft_strdup("bg");
	g_cmd->cmd_list[j + 11] = ft_strdup("kill");
	g_cmd->cmd_list[j + 12] = ft_strdup("alias");
	g_cmd->cmd_list[j + 13] = ft_strdup("unalias");
	g_cmd->cmd_list[j + 14] = ft_strdup("test");
	g_cmd->cmd_list[j + 15] = NULL;
}
