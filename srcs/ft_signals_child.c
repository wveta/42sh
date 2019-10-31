/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/10/31 17:06:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_child(int signo)
{
	if (signo == SIGTSTP || signo == SIGINT || signo == SIGQUIT)
		kill(g_parent_pid, signo);
	signal(SIGINT, ft_signal_child);
	signal(SIGQUIT, ft_signal_child);
	signal(SIGTSTP, ft_signal_child);
	
}
