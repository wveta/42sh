/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 02:09:55 by thaley            #+#    #+#             */
/*   Updated: 2019/12/12 20:58:55 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

// void		take_line_start(void)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 1;
// 	g_input->multiline.start_of_line[0] = i + g_input->prompt_len;
// 	while (i < g_input->input_len)
// 	{
// 		if (count <= g_input->multiline.num_of_lines\
// 			&& g_input->input[i] == '\n' && g_input->input[i + 1])
// 		{
// 			if (i + 1 + g_input->prompt_len % g_input->ws.ws_col == 0)
// 				g_input->multiline.start_of_line[count] = i +\
// 				2 + g_input->prompt_len;
// 			else
// 				g_input->multiline.start_of_line[count] = i\
// 				+ 1 + g_input->prompt_len;
// 			count++;
// 		}
// 		i++;
// 	}
// 	g_input->multiline.start_of_line[count] = 0;
// }

void		take_pos(int save_curs)
{
	int		i;

	if (!save_curs)
	{
		g_input->multiline.pos = g_input->multiline.num_of_lines;
		return ;
	}
	i = save_curs - g_input->prompt_len;
	while (i > 0)
	{
		if (g_input->input[i] == '\n')
			g_input->multiline.pos++;
		i--;
	}
}

void		take_start(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= g_input->multiline.num_of_lines)
	{
		if (i == 0)
			g_input->multiline.start[i] = g_input->prompt_len;
		else
			g_input->multiline.start[i] = (g_input->multiline.end[i - 1] + 1);
		i++;
	}
}

void		count_lines(void)
{
	int		i;
	int		curs;

	i = 0;
	curs = g_input->prompt_len + 1;
	while (i < g_input->input_len)
	{
		if (g_input->input[i] == '\n' && (curs + 1) == g_input->ws.ws_col)
		{
			g_input->multiline.end[g_input->multiline.num_of_lines] = (i - 1) + g_input->prompt_len;
			g_input->multiline.end[g_input->multiline.num_of_lines + 1] = i + g_input->prompt_len;
			g_input->multiline.num_of_lines += 2;
			curs = 0;
		}
		else if (g_input->input[i] == '\n' || curs == g_input->ws.ws_col)
		{
			g_input->multiline.end[g_input->multiline.num_of_lines] = i + g_input->prompt_len;
			g_input->multiline.num_of_lines++;
			curs = 0;
		}
		curs++;
		i++;
	}
	g_input->multiline.end[g_input->multiline.num_of_lines] = g_input->input_len + g_input->prompt_len;
	g_input->multiline.pos = g_input->multiline.num_of_lines;
	take_start();
}
