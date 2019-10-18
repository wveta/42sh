/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_kill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/10/17 12:19:10 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cmd_kill(char **av)
{
	int		sig;
	char	**signame;
	int 	i;
	pid_t	num;
	t_job	*j;

	ft_set_shell("?", "0");	
	signame = ft_split_pipes("HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV \
	SYS PIPE ALRM TERM URG STOP TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM \
	PROF WINCH INFO USR1 USR2");
	sig = 0;
	if (av[1][0] == '-')
	{
		i = -1;
		if (*(av[1] + 1) >= '0' && *(av[1] + 1) <= '9')
		{
			sig = ft_atoi(av[1] + 1);
			i = 1;
		}
		else
		{
			while (signame[++i])
			{
				if (ft_strcmp(av[1] + 1, signame[i]) == 0)
				{
					sig = i + 1;
					i = 1;
					break;
				}
			}
		}
		if (sig == 0)
		{
			ft_print_msg(": kill : invalid signal specification: ", av[1] + 1);
			ft_set_shell("?", "1");	
			return (1);
		}
	}
	else
	{
		sig = 9;
		i = 0;
	}
	ft_free_char_matr(signame);
	while (av[++i])
	{
		num = 0;
		if (av[i][0] == '%')
		{
			num = ft_atoi(av[i] + 1);
			j = g_job_first;
			while (j)
			{
				if (j->num == num)
				{
					num = j->pgid;
					break ;
				}
				j = j->next;
			}
			if (num ==  ft_atoi(av[i] + 1))
			{
				ft_print_msg(": kill : no such job: ", av[i] + 1);
				ft_set_shell("?", "1");			
			}
		}
		else
		{
			num = ft_atoi(av[i]);
			if ((kill(num, 0)) != 0)
			{
				ft_print_msg(" kill : no such process: ", av[i]);					
			}
		}
		kill(num, sig);
	}	
	return (1);
}
