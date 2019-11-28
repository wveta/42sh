/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 19:07:34 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
