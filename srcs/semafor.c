/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semafor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 15:55:30 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_new_semafor(t_cmdlist *cur_cmd)
{
	char	*tmp;
	char	*nr;
	sem_t	*ret;

	tmp = ft_strdup("/");
	nr = ft_strnew(10);
	nr[0] = '\0';
	nr = ft_putfnbr(getpid(), nr);
	tmp = ft_strfjoin(ft_strfjoin(tmp, nr), "_");
	nr[0] = '\0';
	nr = ft_putfnbr(cur_cmd->nr, nr);
	tmp = ft_strfjoin(tmp, nr);
	free(nr);
	if ((ret = sem_open(tmp, O_CREAT, 0644, 0)) != SEM_FAILED)
	{
		cur_cmd->sem_name = ft_strdup(tmp);
		cur_cmd->semafor = ret;
	}
	tmp = ft_strfjoin(tmp, "back");
	if ((ret = sem_open(tmp, O_CREAT, 0644, 0)) != SEM_FAILED)
	{
		cur_cmd->bsem_name = ft_strdup(tmp);
		cur_cmd->bsemafor = ret;
	}
	free(tmp);
}

void	ft_del_semafor(t_cmdlist *cur_cmd)
{
	if (cur_cmd->sem_name)
	{
		sem_close(cur_cmd->semafor);
		sem_unlink(cur_cmd->sem_name);
		free(cur_cmd->sem_name);
	}
	if (cur_cmd->sem_name)
	{
		sem_close(cur_cmd->bsemafor);
		sem_unlink(cur_cmd->bsem_name);
		free(cur_cmd->bsem_name);
	}
}

void	ft_add_semafor(t_pipe *p_head)
{
	t_cmdlist *cur_cmd;
	t_cmdlist *tmp_cmd;

	cur_cmd = p_head->first_cmd;
	tmp_cmd = NULL;
	while (cur_cmd)
	{
		if (tmp_cmd == cur_cmd->next)
		{
			sem_post(cur_cmd->semafor);
			sem_wait(cur_cmd->bsemafor);
			tmp_cmd = cur_cmd;
			if (cur_cmd == p_head->first_cmd)
				break ;
			cur_cmd = p_head->first_cmd;
		}
		else
			cur_cmd = cur_cmd->next;
	}
}

int		ft_wait_semafor(t_cmdlist *cur_cmd)
{
	sem_wait(cur_cmd->semafor);
	sem_post(cur_cmd->bsemafor);
	return (1);
}
