/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:02:01 by thaley            #+#    #+#             */
/*   Updated: 2019/10/23 20:17:00 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	print_loop(char **str, int len)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (len + ft_strlen(str[i]) >= g_input->ws.ws_col - ft_strlen(str[i]))
		{
			len = 0;
			write(1, "\n", 1);
		}
		ft_putstr_fd(str[i], STDIN_FILENO);
		write(1, "  ", 2);
		len = len + ft_strlen(str[i]) + 2;
		i++;
	}
}

void		print_cmds(char **str)
{
	int		len;

	len = 0;
	write(1, "\n", 1);
	print_loop(str, len);
	g_input->auto_tab.amount = 0;
	signal_handler_tab(0);
}
