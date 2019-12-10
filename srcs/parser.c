/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:17:45 by wveta             #+#    #+#             */
/*   Updated: 2019/12/10 17:12:51 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_file_path(char *path, t_listf *first_list)
{
	t_listf			*cur;
	char			*ret;
	unsigned int	hash;

	if (!(path) || !(cur = first_list))
		return (NULL);
	if ((ret = ft_get_hash_path(path)))
		return (ret);
	hash = hashly(path);
	while (cur)
	{
		if (hash == cur->hash && ft_strequ(path, cur->file) == 1)
		{
			ret = ft_strdup(cur->path);
			return (ret);
		}
		cur = cur->next;
	}
	return (NULL);
}

int	ft_parse_cmd(char *str, int len)
{
	char *cmd;
	char **args;
	
	(void)len;
	if  ((str) && ((str[0] == ';') || (str[0] == '&')))
	{
		ft_print_msg(": parse error near ", str);
		return (1);
	}
	if (!(str) || str[0] == '\0' || ft_test_andor() == 0)
		return (0);
	if (!(cmd = ft_strnew((size_t)len)))
		exit_shell();
	if (!(g_job && g_and_or_line))
		ft_set_job_str(str, len);
	cmd = ft_strncpy(cmd, str, (size_t)len);
	if (ft_split_pipes_words(cmd) != 0)
	{
		args = ft_split_pipes(cmd);
		args = ft_get_alias(args);
		if (args && args[0])
		{
			if (ft_strlen(args[0]) > 0)
				ft_do_cmd_shell(args, 0, ft_test_pipe(args, 0));
			args = ft_free_char_matr(args);
		}
		else
		{
			free(cmd);
			ft_print_msg(": parse error near ", str);
			return (1);
		}
	}
	free(cmd);
	return (0);
}

void	ft_init_parse_int(int *i, int *i_cmd, int *qflag, int *br_count)
{
	*i = 0;
	*i_cmd = 0;
	*qflag = 0;
	*br_count = 0;
	g_job_start = NULL;
	g_job_end = 0;
	g_and_or_line = 0;
	g_skip = 0;
	if (g_subst == 0)
		g_job = 0;
}

void	ft_parse_line(char *str)
{
	int		i;
	int		i_cmd;
	int		qflag;
	char 	*av;
	int		br_count;

	ft_init_parse_int(&i, &i_cmd, &qflag, &br_count);
	av = NULL;
	while (str && str[i + i_cmd])
	{	
		if (i == 0 && ft_test_args(str + i_cmd) == 0)
			return ;
		if (i == 0 && g_subst == 0 && ((g_job = ft_test_job(str, i_cmd))) && g_and_or_line)
		{
			av = ft_get_shell_str(g_job_start, g_job_end);
			if (ft_parse_cmd(av, ft_strlen(av)) == 1)
			{
				free(av);
				return ;
			}
			free(av);
			i_cmd = (g_job_start - str) + g_job_end + 1;
			g_job_start = NULL;
			g_job_end = 0;
			g_job = 0;
			i = -1;
		}
		else if (qflag == 0 && str[i + i_cmd] == '"')
			qflag = 1;
		else if (qflag == 0 && str[i + i_cmd] == '\'')
			qflag = 2;
		else if ((qflag == 0 && str[i + i_cmd] == '(' && ((qflag = 3))) ||
				(qflag == 0 && str[i + i_cmd] == '{' && ((qflag = 4))))
			br_count++;
		else if ((qflag == 3 && str[i + i_cmd] == '(') ||
				(qflag == 4 && str[i + i_cmd] == '{'))
			br_count++;	
		else if ((qflag == 3 && str[i + i_cmd] == ')') ||
				(qflag == 4 && str[i + i_cmd] == '}'))
		{
			br_count--;
			if (br_count == 0)
				qflag = 0;
		}
		else if (qflag == 0 && (str[i + i_cmd] == ')' || str[i + i_cmd] == '}')
		&& br_count <= 0)
		{
			ft_print_msg(": parse error: ", str + i_cmd + i);
			return ;
		}	
		else if ((qflag == 1 && str[i + i_cmd] == '"') ||
			(qflag == 2 && str[i + i_cmd] == '\''))
			qflag = 0;
		else if (qflag == 0 && (str[i + i_cmd] == ';' || 
		ft_ampers_test(str, i, i_cmd) == 1))
		{
			if (ft_parse_cmd(str + i_cmd, i) == 1)
				return ;
			i_cmd = i_cmd + i + 1;
			i = -1;
		}
		else if (qflag == 0 && ft_strncmp(str + i + i_cmd, "&&", 2) == 0 
		&& (i + i_cmd == 0 || str[i + i_cmd -1] != '\\'))
		{
			if (ft_parse_cmd(str + i_cmd, i) == 1)
				g_skip = 1;
			i_cmd = i_cmd + i + 2;
			i = 1;
			g_and_or = 1;
		}
		else if (qflag == 0 && ft_strncmp(str + i + i_cmd, "||", 2) ==0 
		&& (i + i_cmd == 0 || str[i + i_cmd -1] != '\\'))
		{
			if (ft_parse_cmd(str + i_cmd, i) == 1)
				g_skip = 1;
			i_cmd = i_cmd + i + 2;
			i = 1 ;
			g_and_or = 2;
		}
		i++;
	}
	ft_parse_cmd(str + i_cmd, i);
	g_job = -1;
}
