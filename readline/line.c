/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:26:47 by thaley            #+#    #+#             */
/*   Updated: 2019/11/27 12:59:31 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_line_up(void)
{
	int		i;
	int		curs;

	i = 0;
	curs = g_input->curs_pos;
	if (g_input->multiline.pos == 0)
		return ;
	while (curs > g_input->multiline.start_if_line[g_input->multiline.pos])
	{
		curs--;
		i++;
	}
	g_input->multiline.pos--;
	ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	g_input->curs_pos = g_input->multiline.start_if_line[g_input->multiline.pos];
	if (g_input->multiline.pos == 0)
	{
		curs = 0;
		while (curs < g_input->prompt_len)
		{
			curs++;
			ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
		}
	}
	while (i > 0 && g_input->input[g_input->curs_pos - g_input->prompt_len] != '\n')
	{
		i--;
		move_right();
	}
}

void		move_line_down(void)
{
	int		i;
	int		curs;

	i = 0;
	curs = g_input->curs_pos;
	if (g_input->multiline.pos == g_input->multiline.num_of_lines)
		return ;
	while (curs > g_input->multiline.start_if_line[g_input->multiline.pos])
	{
		i++;
		curs--;
	}
	g_input->multiline.pos++;
	ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	g_input->curs_pos = g_input->multiline.start_if_line[g_input->multiline.pos];
	while (i > 0 && g_input->curs_pos - g_input->prompt_len < g_input->input_len &&
		g_input->input[g_input->curs_pos - g_input->prompt_len] != '\n')
	{
		i--;
		move_right();
	}
}

void		move_end_of_line(int direction)
{
	int		i;

	i = 0;
	if (direction)
	{
		ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
		g_input->multiline.pos++;
	}
	else
	{
		ft_putstr_fd(tgetstr("up", NULL), STDIN_FILENO);
		g_input->multiline.pos--;
	}
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	g_input->curs_pos = g_input->multiline.start_if_line[g_input->multiline.pos];
	if (!direction)
	{
		if (g_input->multiline.pos == 0)
		{
			while (i < g_input->prompt_len)
			{
				ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
				i++;
			}
		}
		while (g_input->input[g_input->curs_pos - g_input->prompt_len] != '\n')
		{
			g_input->curs_pos++;
			ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
		}
	}
}
