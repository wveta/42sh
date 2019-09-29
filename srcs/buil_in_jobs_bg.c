/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_in_jobs_bg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/09/29 23:02:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cmd_bg(char **av)
{
	t_job	*j;
	int 	i;
	char	*num;
	int		l;

	if ((!(av[1])))
	{
		j = g_job_first;
		while(j)
		{
			if (j->flag == '+')
			{
				kill (-j->pgid, SIGCONT);
				break ;
			}
			j = j->next;
		}
	}
	else
	{
		l = 0;
		while (av && av[++l])
		{
			i = 0;
			j = g_job_first;
			while(j)
			{
				num = ft_num_to_str(j->num);
				if (ft_strcmp(av[l], num) == 0 && ((i = 1)))
					kill (-j->pgid, SIGCONT);
				free(num);
				j = j->next;
			}
			if (i == 0)
			{
				if (av[l])
					ft_print_msg(": jobs: no such job: ", av[l]);
				ft_set_shell("?", "1");
			}
			else
				ft_set_shell("?", "0");
		}
	}	
	return (1);
}


int		ft_cmd_kill(char **av)
{
	(void)av;
	return (1);
}
