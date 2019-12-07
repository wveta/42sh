/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 02:09:55 by thaley            #+#    #+#             */
/*   Updated: 2019/12/08 02:14:23 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		take_line_start(void)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	g_input->multiline.start_of_line[0] = i + g_input->prompt_len;
	while (i < g_input->input_len)
	{
		if (count < g_input->multiline.num_of_lines\
			&& g_input->input[i] == '\n' && g_input->input[i + 1])
		{
			if (i + 1 + g_input->prompt_len % g_input->ws.ws_col == 0)
				g_input->multiline.start_of_line[count] = i +\
				2 + g_input->prompt_len;
			else
				g_input->multiline.start_of_line[count] = i\
				+ 1 + g_input->prompt_len;
			count++;
		}
		i++;
	}
	g_input->multiline.start_of_line[count] = 0;
}

void		take_pos(void)
{
	int		i;

	i = 0;
	if (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
	{
		while (i + 1 <= g_input->multiline.num_of_lines)
		{
			if (g_input->curs_pos == g_input->multiline.start_of_line[i])
			{
				g_input->multiline.pos = i;
				break ;
			}
			else if (g_input->curs_pos > g_input->multiline.start_of_line[i]\
				&& g_input->curs_pos < g_input->multiline.start_of_line[i + 1])
			{
				g_input->multiline.pos = i;
				break ;
			}
			i++;
		}
	}
}

void		count_lines(void)
{
	int		i;

	i = 0;
	g_input->multiline.num_of_lines = 0;
	g_input->multiline.pos = 0;
	if (g_input->multiline.start_of_line)
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
	g_input->multiline.start_of_line =\
	(int *)malloc(sizeof(int) * (g_input->multiline.num_of_lines + 1));
	take_line_start();
	take_pos();
}
