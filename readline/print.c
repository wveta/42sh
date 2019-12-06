/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:09:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/06 23:34:24 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

//check for right work and extra cursors

void		take_line_start(void)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	g_input->multiline.start_if_line[0] = i + g_input->prompt_len;
	while (i < g_input->input_len)
	{
		if (count < g_input->multiline.num_of_lines\
			&& g_input->input[i] == '\n' && g_input->input[i + 1])
		{
			if (i + 1 + g_input->prompt_len % g_input->ws.ws_col == 0)
				g_input->multiline.start_if_line[count] = i + 2 + g_input->prompt_len;
			else
				g_input->multiline.start_if_line[count] = i + 1 + g_input->prompt_len;
			count++;
		}
		i++;
	}
	g_input->multiline.start_if_line[count] = 0;
}

void		count_lines(void)
{
	int		i;

	i = 0;
	g_input->multiline.num_of_lines = 0;
	g_input->multiline.pos = 0;
	if (g_input->multiline.start_if_line)
		free_int_arr();
	while (i < g_input->input_len)
	{
		if (g_input->input[i] == '\n')
			g_input->multiline.num_of_lines++;
		if (i == g_input->curs_pos - g_input->prompt_len)
			g_input->multiline.pos = g_input->multiline.num_of_lines;
		i++;
	}
	if (g_input->multiline.pos == 0)
		g_input->multiline.pos = g_input->multiline.num_of_lines;
	g_input->multiline.start_if_line = (int *)malloc(sizeof(int) * (g_input->multiline.num_of_lines + 1));
	take_line_start();
	if (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
	{
		i = 0;
		while (i + 1 <= g_input->multiline.num_of_lines)
		{
			if (g_input->curs_pos == g_input->multiline.start_if_line[i])
			{
				g_input->multiline.pos = i;
				break ;
			}
			else if (g_input->curs_pos > g_input->multiline.start_if_line[i]\
				&& g_input->curs_pos < g_input->multiline.start_if_line[i + 1])
			{
				g_input->multiline.pos = i;
				break ;
			}
			i++;
		}
	}
}

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

void		print(char *str)
{
	int		i;
	int		save_curs;
	int		curs;
	char	*tmp;
	char	buf[MAX_CMDS];

	i = 0;
	tmp = NULL;
	save_curs = 0;
	curs = take_curs(g_input->curs_pos);
	ft_bzero(buf, MAX_CMDS);
	if (!str)
		return ;
	if (g_input->input_len != g_input->curs_pos - g_input->prompt_len)
	{
		ft_strncpy(buf, g_input->input, g_input->curs_pos - g_input->prompt_len);
		if (str[0] != '\0')
		{
			tmp = ft_strjoin(str, g_input->input + g_input->curs_pos - g_input->prompt_len);
			save_curs = g_input->curs_pos + 1;
		}
		else
		{
			tmp = ft_strdup(g_input->input + g_input->curs_pos - g_input->prompt_len);
			save_curs = g_input->curs_pos;
		}
		ft_bzero(g_input->input, MAX_CMDS);
		ft_strcpy(g_input->input, buf);
		g_input->input_len = g_input->curs_pos - g_input->prompt_len;
	}
	else
		tmp = ft_strdup(str);
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	while (tmp[i])
	{
		if (tmp[i] == '\n' || ft_isprint(tmp[i]))
		{
			g_input->input[(g_input->curs_pos - g_input->prompt_len)] = tmp[i];
			curs++;
			if (tmp[i] == '\n')
			{
				if (curs > 0 && curs % g_input->ws.ws_col == 0)
				{
					// g_input->curs_pos++;
					// g_input->input_len++;
					// g_input->input[(g_input->curs_pos - g_input->prompt_len)] = '\n';
					ft_putchar_fd('\n', STDERR_FILENO);
				}
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
	if (count_n(g_input->input))
		count_lines();
	else
	{
		g_input->multiline.num_of_lines = 0;
		g_input->multiline.pos = 0;
		if (g_input->multiline.start_if_line)
			free_int_arr();
	}
	if (save_curs > 0)
	{
		while(g_input->curs_pos > save_curs)
		{
			move_left();
		}
	}
	free(tmp);
}
