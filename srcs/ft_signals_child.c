/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/11/26 17:43:28 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_child(int signo)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 4);
	tmp[0] = '\0';
	ft_print_msg(": signal in child: ", ft_putfnbr(signo, tmp));
	free(tmp);
	if (signo == SIGTSTP)
		kill(g_parent_pid, SIGTSTP);
//	signal(SIGINT, ft_signal_child);
//	signal(SIGQUIT, ft_signal_child);
	signal(SIGTSTP, ft_signal_child);
}

void	ft_print_sig(int status)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 10);
	tmp[0] = '\0';
	if (tmp)
	{
		if (WIFSTOPPED(status))
			ft_print_msg(" : signal :", ft_putfnbr(WSTOPSIG(status), tmp));
		else if (WIFSIGNALED(status))
			ft_print_msg(" : signal :", ft_putfnbr(WTERMSIG(status), tmp));
	}
	free(tmp);
}
