/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:48:56 by thaley            #+#    #+#             */
/*   Updated: 2019/11/27 18:10:04 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_signal_win_size(int signo)
{
	(void)signo;
	go_home_pos();
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	// ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	g_input->curs_pos = g_input->prompt_len + g_input->input_len;
	ft_putstr_fd(g_input->input, STDERR_FILENO);
	longjmp(g_cmd->ebuf2, g_cmd->jmp_code2);
}
