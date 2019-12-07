/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:09:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/08 02:10:25 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			take_curs(int curs_pos)
{
	int		curs;
	int		i;

	i = curs_pos;
	curs = 0;
	if (ft_strchr(g_input->input, '\n'))
	{
		while (i > g_input->prompt_len &&\
		g_input->input[(i - g_input->prompt_len) - 1] != '\n')
		{
			i--;
			curs++;
		}
		if (i == g_input->prompt_len)
			curs += g_input->prompt_len;
	}
	else if (i >= g_input->ws.ws_col)
	{
		while (i / g_input->ws.ws_col)
			i %= g_input->ws.ws_col;
		curs = i;
	}
	else
		curs = i;
	return (curs);
}

int			count_n(char *str)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1])
			n++;
		i++;
	}
	return (n);
}

char		*check_curs_pos(int *save_curs, char *buf, char *str, char *tmp)
{
	if (g_input->input_len != g_input->curs_pos - g_input->prompt_len)
	{
		ft_strncpy(buf, g_input->input, g_input->curs_pos\
					- g_input->prompt_len);
		if (str[0] != '\0')
		{
			tmp = ft_strjoin(str, g_input->input +\
			g_input->curs_pos - g_input->prompt_len);
			*save_curs = g_input->curs_pos + 1;
		}
		else
		{
			tmp = ft_strdup(g_input->input +\
			g_input->curs_pos - g_input->prompt_len);
			*save_curs = g_input->curs_pos;
		}
		ft_bzero(g_input->input, MAX_CMDS);
		ft_strcpy(g_input->input, buf);
		g_input->input_len = g_input->curs_pos - g_input->prompt_len;
	}
	else
		tmp = ft_strdup(str);
	return (tmp);
}

void		print_loop(char *tmp, int curs)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n' || ft_isprint(tmp[i]))
		{
			g_input->input[(g_input->curs_pos - g_input->prompt_len)] = tmp[i];
			curs++;
			if (tmp[i] == '\n')
			{
				if (curs > 0 && curs % g_input->ws.ws_col == 0)
					ft_putchar_fd('\n', STDERR_FILENO);
				curs = -1;
			}
			g_input->curs_pos++;
			ft_putchar_fd(tmp[i], STDERR_FILENO);
			if (curs != 0 && curs % g_input->ws.ws_col == 0)
				ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
			g_input->input_len++;
		}
		i++;
	}
}

void		print(char *str)
{
	int		save_curs;
	int		curs;
	char	*tmp;
	char	buf[MAX_CMDS];

	tmp = NULL;
	save_curs = 0;
	curs = take_curs(g_input->curs_pos);
	ft_bzero(buf, MAX_CMDS);
	if (!str)
		return ;
	tmp = check_curs_pos(&save_curs, buf, str, tmp);
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	print_loop(tmp, curs);
	if (count_n(g_input->input))
		count_lines();
	else
		null_multiline();
	if (save_curs > 0)
	{
		while (g_input->curs_pos > save_curs)
			move_left();
	}
	free(tmp);
}
