/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:26:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/09 11:06:37 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_line_up(void)
{
	int		i;
	int		check_curs;

	i = -1;
	check_curs = take_curs(g_input->curs_pos);
	if (g_input->multiline.pos == 0)
		return ;
	if (g_input->input[(g_input->curs_pos - g_input->prompt_len)] == '\n')
	{
		move_left();
		if (g_input->input[(g_input->curs_pos - g_input->prompt_len)] != '\n')
			i++;
	}
	while (g_input->curs_pos > g_input->prompt_len &&\
	(check_curs + 1) % g_input->ws.ws_col != 0 &&\
	g_input->input[(g_input->curs_pos - g_input->prompt_len)] != '\n')
	{
		move_left();
		check_curs = take_curs(g_input->curs_pos);
		i++;
	}
	check_curs = take_curs(g_input->curs_pos);
	while (g_input->curs_pos > g_input->prompt_len &&\
	check_curs % g_input->ws.ws_col != 0 &&\
	g_input->input[(g_input->curs_pos - g_input->prompt_len) - 1] != '\n')
	{
		move_left();
		check_curs = take_curs(g_input->curs_pos);
	}
	while (i > 0 && (g_input->curs_pos - g_input->prompt_len)\
	< g_input->input_len && g_input->input[(g_input->curs_pos\
	- g_input->prompt_len)] != '\n' && (check_curs + 1) %\
	g_input->ws.ws_col != 0)
	{
		move_right();
		i--;
		check_curs = take_curs(g_input->curs_pos);
	}
}

void		move_line_down(void)
{
	int		check_curs;
	int		save_curs;
	int		i;

	check_curs = -1;
	i = 0;
	if (g_input->multiline.pos == g_input->multiline.num_of_lines)
		return ;
	save_curs = g_input->curs_pos - g_input->prompt_len;
	while (save_curs > 0 && (g_input->input[save_curs - 1] != '\n'\
			&& check_curs % g_input->ws.ws_col != 0))
	{
		save_curs--;
		i++;
		check_curs = take_curs(g_input->curs_pos - i);
	}
	check_curs = -1;
	if (g_input->input[(g_input->curs_pos - g_input->prompt_len)] == '\n'\
	&& g_input->input[(g_input->curs_pos - g_input->prompt_len) - 1] == '\n')
	{
		move_right();
		return ;
	}
	if (i == 0 && g_input->input[(g_input->curs_pos -\
		g_input->prompt_len) - 1] == '\n')
		move_right();
	while ((g_input->curs_pos - g_input->prompt_len) < g_input->input_len &&\
	(check_curs % g_input->ws.ws_col != 0 && g_input->input[(g_input->curs_pos\
	- g_input->prompt_len) - 1] != '\n'))
	{
		move_right();
		check_curs = take_curs(g_input->curs_pos);
	}
	while (i > 0 && (g_input->curs_pos - g_input->prompt_len) <\
	g_input->input_len && g_input->input[(g_input->curs_pos -\
	g_input->prompt_len)] != '\n' && (check_curs + 1) % g_input->ws.ws_col != 0)
	{
		move_right();
		i--;
		check_curs = take_curs(g_input->curs_pos);
	}
}

static void	move_end_upper(void)
{
	int		i;

	i = 0;
	if (g_input->multiline.pos == 0)
	{
		while (i < g_input->prompt_len)
		{
			ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
			i++;
		}
	}
	while (g_input->input[g_input->curs_pos - g_input->prompt_len] != '\n')
		move_right();
}

void		move_end_of_line(int direction)
{
	int		curs;

	curs = 0;
	if (direction)
	{
		ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
		g_input->multiline.pos++;
		g_input->curs_pos++;
	}
	else
	{
		ft_putstr_fd(tgetstr("up", NULL), STDIN_FILENO);
		g_input->multiline.pos--;
		g_input->curs_pos--;
		if (g_input->input[(g_input->curs_pos -\
			g_input->prompt_len) - 1] != '\n' && (curs = take_curs(g_input->curs_pos)) % g_input->ws.ws_col != 0)
		{
			g_input->curs_pos--;
			while (g_input->curs_pos > g_input->prompt_len\
				&& g_input->input[(g_input->curs_pos -\
				g_input->prompt_len) - 1] != '\n')
				g_input->curs_pos--;
		}
	}
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	if (!direction)
		move_end_upper();
}
