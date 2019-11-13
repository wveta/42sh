/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/11/12 22:26:21 by wveta            ###   ########.fr       */
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
				char *nr;
				tmp = ft_strnew(1000);
				nr = ft_strnew(10);
				tmp[0] = '\0';
				tmp = ft_strjoin(tmp, "\n Signal in fork ");
				nr[0] = '\0';
				nr = ft_putfnbr(signo, nr);
				tmp = ft_strjoin(tmp, nr);
				ft_rec_log(tmp);
	
	if (signo == SIGTSTP)
		kill(g_parent_pid, SIGTSTP);
	signal(SIGINT, ft_signal_child);
	signal(SIGQUIT, ft_signal_child);
	signal(SIGTSTP, ft_signal_child);
}
