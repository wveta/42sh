/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:26:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/15 18:31:25 by thaley           ###   ########.fr       */
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

void		scroll_top(void)
{
	int		curs;
	int		i;
	char	buf[20];

	i = 0;
	curs = 0;
	ft_bzero(buf, 20);
	ft_putstr_fd("\e[6n", STDIN_FILENO);
	read(STDIN_FILENO, &buf, 20);
	while (buf[i] && !ft_isdigit(buf[i]))
		i++;
	curs = ft_atoi(buf + i);
	if (curs == 1)
		return ;
	while (curs > 0)
	{
		ft_putstr_fd(tgetstr("sr", NULL), STDERR_FILENO);
		curs--;
	}
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	ft_putstr_fd(g_input->input, STDERR_FILENO);
}
