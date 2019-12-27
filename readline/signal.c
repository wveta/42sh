/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:48:56 by thaley            #+#    #+#             */
/*   Updated: 2019/12/27 12:14:55 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_signal_win_size(int signo)
{
	(void)signo;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	null_multiline();
	count_lines();
}
