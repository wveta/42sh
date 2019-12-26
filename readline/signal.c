/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:48:56 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 19:27:34 by thaley           ###   ########.fr       */
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
		tputs(tgetstr("up", NULL), 1, putint);
		g_input->multiline.pos--;
	}
	tputs(tgetstr("cr", NULL), 1, putint);
	tputs(tgetstr("cd", NULL), 1, putint);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	g_input->curs_pos = g_input->prompt_len;
	g_input->input_len = 0;
	print(tmp);
}
