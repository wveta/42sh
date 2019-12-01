/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:06:59 by thaley            #+#    #+#             */
/*   Updated: 2019/11/29 23:28:15 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	delete_char_two(void)
{
	if (g_input->curs_pos == g_input->input_len + g_input->prompt_len)
		return ;
	if (g_input->curs_pos == g_input->prompt_len)
		ft_memmove(g_input->input + (g_input->curs_pos - g_input->prompt_len), g_input->input +
				(g_input->curs_pos - g_input->prompt_len) + 1, MAX_CMDS - (g_input->curs_pos - g_input->prompt_len));
	else
		ft_memmove(g_input->input + (g_input->curs_pos - g_input->prompt_len), g_input->input +
				(g_input->curs_pos - g_input->prompt_len) + 1, MAX_CMDS - (g_input->curs_pos - g_input->prompt_len) - 1);
	g_input->input_len--;
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
	if (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
		print("\0");
}

void	delete_char(void)
{
	if (g_input->curs_pos - g_input->prompt_len == 0)
		return ;
	move_left();
	ft_memmove(g_input->input + (g_input->curs_pos - g_input->prompt_len), g_input->input +\
				(g_input->curs_pos - g_input->prompt_len) + 1,\
				MAX_CMDS - (g_input->curs_pos - g_input->prompt_len) - 1);
	g_input->input_len--;
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
	if (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
		print("\0");
}
