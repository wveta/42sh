/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:44:06 by thaley            #+#    #+#             */
/*   Updated: 2019/12/01 08:57:59 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*find_word(curs)
{
	char	*tmp;
	int		i;

	i = curs;
	tmp = NULL;
	if (i > 0)
	{
		while (i > 0 && g_input->input[i - 1] > 32)
		{
			i--;
			if (i == 0 || (i > 0 && g_input->input[i - 1] < 33))
			{
				tmp = ft_strsub(g_input->input, i, curs - i);
				while (--i > -1)
				{
					if (g_input->input[i] > 32)
						g_input->autocompl.file = 1;
				}
				if (tmp[0] == '/' || tmp[0] == '~' || (tmp[0] == '.' && tmp[1] && tmp[1] == '.')\
			|| (tmp[0] == '.' && tmp[1] && tmp[1] == '/'))
					g_input->autocompl.file = 1;
				else if (i == -1)
					g_input->autocompl.cmd = 1;
				break ;
			}
		}
		if (!tmp && i > 0)
		{
			while (i > 0 && g_input->input[i] < 33)
				i--;
			if (i > 0 && (i + 1) != curs)
				g_input->autocompl.file = 1;
			else if (i == 0 && g_input->input[i] < 33)
			{
				g_input->autocompl.cmd = 1;
				return (NULL);
			}
			else if (i == 0 && g_input->input[i] > 32)
			{
				g_input->autocompl.cmd = 1;
				tmp = ft_strsub(g_input->input, 0, 1);
			}
		}
	}
	if (g_input->autocompl.cmd == 0 && g_input->autocompl.file == 0)
	{
		if (i == 0 && g_input->input[i] < 33)
		{
			g_input->autocompl.cmd = 1;
			return (NULL);
		}
		else if (i == 0 && g_input->input[i] > 32)
		{
			tmp = ft_strsub(g_input->input, 0, 1);
			if (tmp[0] == '/' || tmp[0] == '~' || (tmp[0] == '.' && tmp[1] && tmp[1] == '.')\
			|| (tmp[0] == '.' && tmp[1] && tmp[1] == '/'))
				g_input->autocompl.file = 1;
			else
				g_input->autocompl.cmd = 1;
		}
	}
	return (tmp);
}

void	all_cmd(void)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	write(STDERR_FILENO, "\n", 1);
	while (g_cmd->cmd_list[i])
	{
		len += ft_strlen(g_cmd->cmd_list[i]);
		if (len >= g_input->ws.ws_col)
		{
			len = ft_strlen(g_cmd->cmd_list[i]);
			ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
			ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
		}
		len += 3;
		ft_putstr_fd(g_cmd->cmd_list[i], STDERR_FILENO);
		if (len < g_input->ws.ws_col)
			ft_putstr_fd("   ", STDERR_FILENO);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
}

void	take_search_info(void)
{
	int		curs;
	char	*tmp;

	tmp = NULL;
	curs = g_input->curs_pos - g_input->prompt_len;
	g_input->autocompl.tab_count++;
	if (g_input->input_len == 0)
	{
		if (g_input->autocompl.tab_count == 2)
		{
			all_cmd();
			g_input->autocompl.tab_count = 0;
		}
	}
	else
	{
		tmp = find_word(curs);
		if (g_input->autocompl.file)
			find_file(tmp);
		else
			find_cmd(tmp);
		if (tmp)
			free(tmp);
	}
}

void	find_name(void)
{
	take_search_info();
}

int		autocmp(char *str)
{
	if (str[0] == TAB && !str[1])
	{
		find_name();
		if (!g_input->autocompl.tab_count)
			null_autocmpl();
		return (1);
	}
	return (0);
}
