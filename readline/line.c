/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:26:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/12 21:47:55 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_line_up(void)
{
	int		i;
	int		prompt;

	i = 0;
	prompt = -1;
	if (g_input->multiline.pos == 0)
		return ;
	while ((g_input->curs_pos - i) >\
		g_input->multiline.start[g_input->multiline.pos])
		i++;
	ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	g_input->multiline.pos--;
	g_input->curs_pos = g_input->multiline.start[g_input->multiline.pos];
	if (g_input->multiline.pos == 0)
	{
		while (++prompt < g_input->prompt_len)
			ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
	}
	while (i > 0 && g_input->curs_pos <\
		g_input->multiline.end[g_input->multiline.pos])
	{
		i--;
		move_right();
	}
}

void		move_line_down(void)
{
	int		i;

	i = 0;
	if (g_input->multiline.pos == g_input->multiline.num_of_lines)
		return ;
	while ((g_input->curs_pos - i) >\
		g_input->multiline.start[g_input->multiline.pos])
		i++;
	ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
	g_input->multiline.pos++;
	g_input->curs_pos = g_input->multiline.start[g_input->multiline.pos];
	while (i > 0 && g_input->curs_pos <\
		g_input->multiline.end[g_input->multiline.pos])
	{
		i--;
		move_right();
	}
}

void		move_end_of_line(void)
{
	int		i;

	i = -1;
	ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
	g_input->curs_pos--;
	g_input->multiline.pos--;
	if (g_input->multiline.pos == 0)
	{
		while (++i < g_input->prompt_len)
			ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
	}
	i = g_input->multiline.start[g_input->multiline.pos];
	while (i < g_input->multiline.end[g_input->multiline.pos])
	{
		ft_putstr_fd(tgetstr("nd", NULL), STDERR_FILENO);
		i++;
	}
}
