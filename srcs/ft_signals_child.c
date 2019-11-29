/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/11/29 15:21:33 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_sig(pid_t pid, int signo, int status)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 400);
	tmp[0] = '\n';
	tmp[1] = '\0';
	tmp = ft_strjoin(tmp, "pid = ");
	if (pid)
		tmp = ft_add_strnum(tmp, pid);
	else
		tmp = ft_add_strnum(tmp, getpid());
	if (tmp)
	{
		if (signo)
		{
			tmp = ft_strjoin(tmp, " signo =");
			tmp = ft_add_strnum(tmp, signo);
		}
		if (status)
		{
			if (WIFSTOPPED(status))
			{
				tmp = ft_strjoin(tmp, " stopped by =");
				tmp = ft_add_strnum(tmp, WSTOPSIG(status));
			}
			else if (WIFSIGNALED(status))
			{
				tmp = ft_strjoin(tmp, " finished by =");
				tmp = ft_add_strnum(tmp, WTERMSIG(status));
			}
		}
	}
	if (g_signal == 1)
		ft_print_msg(" : Info signal :", tmp);
	ft_rec_log(tmp);
	free(tmp);
}
