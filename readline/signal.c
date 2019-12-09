/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:48:56 by thaley            #+#    #+#             */
/*   Updated: 2019/12/08 03:55:36 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_signal_win_size(int signo)
{
	char	tmp[MAX_CMDS];

	(void)signo;
	ft_bzero(tmp, MAX_CMDS);
	ft_strcpy(tmp, g_input->input);
	ft_bzero(g_input->input, MAX_CMDS);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	while (g_input->multiline.pos > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), STDERR_FILENO);
		g_input->multiline.pos--;
	}
	ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	if (g_input->multiline.fake_curs != -1)
	{
		ft_memmove(g_input->input + (g_input->multiline.fake_curs - g_input->prompt_len)\
		, g_input->input + (g_input->multiline.fake_curs - g_input->prompt_len) + 1\
		, MAX_CMDS - (g_input->multiline.fake_curs - g_input->prompt_len) - 1);
		g_input->multiline.fake_curs = -1;	
	}
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	g_input->curs_pos = g_input->prompt_len;
	g_input->input_len = 0;
	print(tmp);
	longjmp(g_cmd->ebuf2, g_cmd->jmp_code2);
}
