/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:10:12 by wveta             #+#    #+#             */
/*   Updated: 2019/08/29 21:06:12 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_cmd_matr(t_listf *lst)
{
	int		j;
	int		count;
	t_listf	*cur;

	count = ft_len_list(lst);
	if (!(g_cmd->cmd_list = (char **)malloc(sizeof(char *) * (count + 4 + 1))))
		exit_shell();
	j = 0;
	cur = lst;
	while (j < count)
	{
		if (!(g_cmd->cmd_list[j] = ft_strdup(cur->file)))
		{
			g_cmd->cmd_list = ft_free_char_matr(g_cmd->cmd_list);
			exit_shell();
		}
		cur = cur->next;
		j++;
	}
	g_cmd->cmd_list[j] = ft_strdup("exit");
	g_cmd->cmd_list[j + 1] = ft_strdup("setenv");
	g_cmd->cmd_list[j + 2] = ft_strdup("unsetenv");
	g_cmd->cmd_list[j + 3] = ft_strdup("env");
	g_cmd->cmd_list[j + 4] = NULL;
}

int		ft_get_ind_env(char *s)
{
	int i;

	if (!(g_envi->env) || !(s))
		return (-1);
	i = 0;
	while (g_envi->env[i])
	{
		if (ft_strncmp(g_envi->env[i], s, ft_strlen(s)) == 0
		&& g_envi->env[i][ft_strlen(s)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

t_listf	*ft_add_file(t_listf *first_list, char *full)
{
	t_listf *cur;
	char	*file;

	file = ft_get_file(full);
	if (!(cur = malloc(sizeof(t_listf))))
		exit_shell();
	cur->file = file;
	cur->path = full;
	cur->hash = hashly(file);
	cur->next = first_list;
	return (cur);
}

t_listf	*ft_add_exe_list(char *paths, int lpath, t_listf *first_list)
{
	DIR				*pdir;
	struct dirent	*drn;
	char			*path;
	char			*full;

	path = ft_set_dirpath(lpath, paths);
	if ((pdir = opendir(path)))
	{
		while ((drn = readdir(pdir)) != NULL)
		{
			if (!((ft_strequ(drn->d_name, ".")) ||
			(ft_strequ(drn->d_name, ".."))))
			{
				full = ft_alloc_char(lpath + drn->d_namlen + 2);
				full = ft_set_full_exe(drn->d_name, path, full);
				if (access(full, F_OK) == 0 && access(full, X_OK) == 0)
					first_list = ft_add_file(first_list, full);
				else
					free(full);
			}
		}
		closedir(pdir);
	}
	free(path);
	return (first_list);
}

t_listf	*ft_create_exe_list(void)
{
	int i;
	int j;
	int l;

	g_envi->first_list = NULL;
	ft_set_var_ex_lst(&i, &j, &l);
	while (i != -1 && g_envi->env[i][j + l])
	{
		if (g_envi->env[i][j + l] == ':')
		{
			g_envi->first_list = ft_add_exe_list(&g_envi->env[i][j],
			l, g_envi->first_list);
			j = j + l + 1;
			l = 0;
		}
		else
			l++;
	}
	if (i > -1)
		g_envi->first_list = ft_add_exe_list(&g_envi->env[i][j],
		l, g_envi->first_list);
	ft_merge_sort(&g_envi->first_list);
	ft_get_cmd_matr(g_envi->first_list);
	return (g_envi->first_list);
}
