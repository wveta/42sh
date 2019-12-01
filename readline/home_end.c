/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:21:27 by thaley            #+#    #+#             */
/*   Updated: 2019/11/27 13:38:58 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		go_home_pos(void)
{
	int		curs;

	curs = g_input->curs_pos - g_input->prompt_len;
	if (curs == 0)
		return ;
	while (g_input->curs_pos > g_input->prompt_len)
		move_left();
}

void		go_end_pos(void)
{
	int		curs;

	curs = g_input->curs_pos - g_input->prompt_len;
	if (curs == g_input->input_len)
		return ;
	while (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
		move_right();
}
