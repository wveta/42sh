/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:10:19 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/11 10:18:00 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			del_str(void *content, size_t size)
{
	ft_memdel(&content);
	(void)size;
}

static void		ft_globbing_addline(char *line, t_list **alist)
{
	t_list	*list;

	if (!(list = ft_memalloc(sizeof(t_list))))
		exit(1);
	list->content = ft_strdup(line);
	list->next = 0;
	ft_lstadd_last(alist, list);
}

static bool		ft_globbing_split(char *line, char **path, char **pat)
{
	size_t	i;
	int		len;

	i = -1;
	len = -1;
	*path = 0;
	*pat = 0;
	while (line[++i])
		if (line[i] == '/')
			len = i;
	if (!line[len + 1])
		return (false);
	if (len != -1)
		if (!(*path = ft_strndup(line, len + 1)))
			exit(1);
	if (!(*pat = ft_strdup(line + len + 1)))
		exit(1);
	return (true);
}

static t_list	*ft_globbing_path_cycle(DIR *dir, char *path, char *pat)
{
	t_dir	*entry;
	t_list	*list;
	char	*join_line;

	list = 0;
	while ((entry = readdir(dir)))
	{
		if (pat[0] != '.' && entry->d_name[0] == '.')
			continue ;
		if (ft_strcmp(entry->d_name, "..") &&\
				ft_strcmp(entry->d_name, ".") &&\
				glob_check(entry->d_name, pat, 0, 0))
		{
			if (!(
					join_line = glob_join(path, entry->d_name)
//				join_line = ft_strjoin(path, entry->d_name)
				))
				exit(1);
			ft_globbing_addline(join_line, &list);
			free(join_line);
		}
	}
	if (list)
		ft_lst_sort(&list, &ft_strcmp);
	return (list);
}

static int		ft_globbing_getdir(char *path, DIR **dir)
{
	if (!path)
		if (!(*dir = opendir(".")))
			return (0);
	if (path && *path)
		if (!(*dir = opendir(path)))
			return (0);
	return (1);
}

/*static void	ft_globbing_cycle(char *line, t_list **alist)
{
	DIR		*dir;
	t_list	*list;
	char	*path;
	char	*pat;

	if (!ft_globbing_split(line, &path, &pat))
			return (ft_globbing_addline(line, alist));
	if (ft_globbing_getdir(path, &dir))
	{
		if ((list = ft_globbing_path_cycle(dir, path, pat)))
			ft_lstadd_last(alist, list);
		else
			ft_globbing_addline(line, alist);
	}
	if (dir)
		closedir(dir);
	if (path)
		ft_strdel(&path);
	if (pat)
		ft_strdel(&pat);
}*/

static void		ft_globbing_cycle(char *line, t_list **alist)
{
	DIR			*dir;
	t_list		*list;
	char		*path;
	char		*pat;

	if (!ft_globbing_split(line, &path, &pat))
		return (ft_globbing_addline(line, alist));
	if (!ft_globbing_getdir(path, &dir))
		ft_globbing_addline(line, alist);
	else
	{
		if ((list = ft_globbing_path_cycle(dir, path, pat)))
			ft_lstadd_last(alist, list);
		else
			ft_globbing_addline(line, alist);
	}
	if (dir)
		closedir(dir);
	if (path)
		ft_strdel(&path);
	if (pat)
		ft_strdel(&pat);
}

void			ft_globbing_listtoline(t_list *list, char ***table)
{
	char		**ret;
	int			i;

	i = ft_lstsize(list);
	if (!(ret = ft_memalloc(sizeof(char*) * (i + 1))))
		exit(1);
	i = -1;
	while (list)
	{
		if (!(ret[++i] = ft_strdup(list->content)))
			exit(1);
		list = list->next;
	}
	*table = ret;
}

char			**ft_globbing(char **table)
{
	t_list		*list;
	int			i;
	char		**ret;

	if (!table || !*table)
		return (0);
	i = -1;
	list = 0;
	while (table[++i])
		ft_globbing_cycle(table[i], &list);
	ft_free_table(&table);
	ft_globbing_listtoline(list, &ret);
	ft_lstdel(&list, &del_str);
	return (ret);
}
