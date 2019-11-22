/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_kill2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/22 12:36:04 by wveta            ###   ########.fr       */
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
	t_proc	*p;

	ft_set_shell("?", "0");	
	signame = ft_split_pipes("HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV \
	SYS PIPE ALRM TERM URG STOP TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM \
	PROF WINCH INFO USR1 USR2");
	sig = 0;
	if (av[1] && av[1][0] == '-')
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
				if (j->num == num || (num == 0 && j->flag == '+'))
				{
//					num = j->pgid;
					p = j->first_proc;
					while (p)
					{
						num = p->pid;
						kill(num, sig);
						p = p->next;
					}
					break;
				}
				j = j->next;
			}
			if (num ==  ft_atoi(av[i] + 1))
			{
				ft_print_msg(": kill : no such job: ", av[i] + 1);
				ft_set_shell("?", "1");
				continue ;		
			}
		}
		else
		{
			num = ft_atoi(av[i]);
			if ((kill(num, 0)) != 0)
			{
				ft_print_msg(" kill : no such process: ", av[i]);
				continue ;					
			}
			kill(num, sig);
		}
		
	}	
	return (1);
}

void	ft_set_cmd_exit_status(int status)
{
	char	*tmp;
	int 	i;

	tmp = malloc(sizeof(char) * 3);
	if (tmp)
	{
		tmp[0] = '\0';
		if ((WIFEXITED(status)) && (i = WEXITSTATUS(status)) != 0)
			ft_set_shell("?", "1");
		else if ((WIFEXITED(status)) && (i = WEXITSTATUS(status)) == 0)
			ft_set_shell("?", "0");			
		else if (WIFSTOPPED(status))
			ft_set_shell("?", ft_putfnbr(WSTOPSIG(status), tmp));
		else if (WIFSIGNALED(status))
			ft_set_shell("?", ft_putfnbr(WTERMSIG(status), tmp));
		else if (WIFCONTINUED(status))
			ft_set_shell("?", "0");
		else
			ft_set_shell("?", "1");
		free(tmp);
	}
}

void	ft_rec_log(char *str)
{
	int i;

	i = open("/Users/wveta/21old/pipelog", O_WRONLY| O_CREAT | O_APPEND , 0644);
	if (i != -1)
	{
		write(i, str, ft_strlen(str));
	}
	close(i);
}
