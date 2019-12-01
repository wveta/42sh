/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:08:06 by thaley            #+#    #+#             */
/*   Updated: 2019/12/01 08:34:37 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_curs_end(void)
{
	int		i;

	i = 0;
	ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	while (i < g_input->ws.ws_col && g_input->input[i - g_input->prompt_len] != '\n')
	{
		ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
		i++;
	}
}

void		move_left(void)
{
	int		check_curs;

	check_curs = take_curs(g_input->curs_pos);
	if (g_input->curs_pos - g_input->prompt_len == 0)
		return ;
	if (g_input->multiline.pos > 0 &&\
		g_input->multiline.start_if_line[g_input->multiline.pos] == g_input->curs_pos)
		move_end_of_line(0);
	else if (check_curs != 0 && check_curs % g_input->ws.ws_col == 0)
	{
		g_input->curs_pos--;
		move_curs_end();
	}
	else
	{
		g_input->curs_pos--;
		ft_putstr_fd(tgetstr("le", NULL), STDERR_FILENO);
	}
}

void		move_right(void)
{
	int		check_curs;

	check_curs = take_curs(g_input->curs_pos);
	if (g_input->curs_pos - g_input->prompt_len == g_input->input_len)
		return ;
	if (g_input->multiline.pos < g_input->multiline.num_of_lines &&
		g_input->input[g_input->curs_pos - g_input->prompt_len] == '\n')
		move_end_of_line(1);
	else if (check_curs + 1 % g_input->ws.ws_col == 0)
	{
		g_input->curs_pos++;
		ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
		ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	}
	else
	{
		g_input->curs_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
	}
}

void		move_word_left(void)
{
	if (g_input->curs_pos - g_input->prompt_len == 0)
		return ;
	while (g_input->curs_pos - g_input->prompt_len > 0 && (g_input->input[g_input->curs_pos - g_input->prompt_len] < 33\
		|| g_input->input[g_input->curs_pos - g_input->prompt_len - 1] < 33))
		move_left();
	while (g_input->curs_pos - g_input->prompt_len > 0 && g_input->input[g_input->curs_pos - g_input->prompt_len - 1] > 32\
		&& g_input->input[g_input->curs_pos - g_input->prompt_len - 1] < 127)
		move_left();
}

void		move_word_right(void)
{
	int		curs;

	curs = g_input->curs_pos - g_input->prompt_len;
	if (curs == g_input->input_len)
		return ;
	while (g_input->curs_pos - g_input->prompt_len < g_input->input_len && g_input->input[g_input->curs_pos - g_input->prompt_len] < 33)
		move_right();
	while (g_input->curs_pos - g_input->prompt_len < g_input->input_len && g_input->input[g_input->curs_pos - g_input->prompt_len] > 32\
		&& g_input->input[g_input->curs_pos - g_input->prompt_len] < 127)
		move_right();
}
