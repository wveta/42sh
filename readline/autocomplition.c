/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:44:06 by thaley            #+#    #+#             */
/*   Updated: 2019/12/07 23:06:19 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
		tmp = find_key(curs);
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
