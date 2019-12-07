/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:16:11 by thaley            #+#    #+#             */
/*   Updated: 2019/12/08 00:28:22 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		count_file_match(char *key)
{
	struct dirent	*dn;
	DIR				*dir;

	dir = NULL;
	if (!(dir = opendir(g_input->autocompl.path)))
		return ;
	while ((dn = readdir(dir)))
	{
		if (ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, ".."))
		{
			if (key && !ft_strncmp(dn->d_name, key, ft_strlen(key)))
				g_input->autocompl.amount++;
			else if (!key)
				g_input->autocompl.amount++;
		}
	}
	g_input->autocompl.seach_res = (char **)malloc(sizeof(char *)\
								* (g_input->autocompl.amount + 1));
	closedir(dir);
}

void		find_match(char *key)
{
	struct dirent	*dn;
	DIR				*dir;
	int				i;

	i = 0;
	if (!(dir = opendir(g_input->autocompl.path)))
		return ; //error msg
	while ((dn = readdir(dir)))
	{
		if (ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, ".."))
		{
			if (key && !ft_strncmp(dn->d_name, key, ft_strlen(key)))
				g_input->autocompl.seach_res[i++] = ft_strdup(dn->d_name);
			else if (!key)
				g_input->autocompl.seach_res[i++] = ft_strdup(dn->d_name);
		}
	}
	closedir(dir);
	g_input->autocompl.seach_res[g_input->autocompl.amount] = NULL;
}

void		all_files_in_path(void)
{
	DIR				*dir;
	struct dirent	*dn;
	int				i;

	i = 0;
	dir = NULL;
	count_file_match(NULL);
	if (!(dir = opendir(g_input->autocompl.path)))
		return ; //print_error_msg
	while ((dn = readdir(dir)))
	{
		if (ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, ".."))
		{
			g_input->autocompl.seach_res[i] = ft_strdup(dn->d_name);
			i++;
		}
	}
	closedir(dir);
}

void		find_file(char *key)
{
	char			*tmp;

	tmp = NULL;
	if (g_input->autocompl.tab_count < 2)
	{
		if (!key)
		{
			g_input->autocompl.path = ft_get_env("PWD");
			all_files_in_path();
		}
		else
			tmp = parse_path(key);
	}
	if (g_input->autocompl.amount > 1 && g_input->autocompl.tab_count == 2)
	{
		ascii_sort(g_input->autocompl.seach_res);
		print_array(g_input->autocompl.seach_res);
	}
	else if (g_input->autocompl.amount == 1)
		change_input(g_input->autocompl.seach_res, tmp);
	ft_free(tmp);
}
