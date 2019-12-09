/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_autocmpl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:38:22 by thaley            #+#    #+#             */
/*   Updated: 2019/12/09 11:19:07 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		return_cursor(void)
{
	int		i;

	i = 0;
	g_input->curs_pos = g_input->autocompl.save_curs;
	if (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
	{
		while ((g_input->curs_pos - g_input->prompt_len)\
				+ i != g_input->input_len)
		{
			ft_putstr_fd(tgetstr("le", NULL), STDERR_FILENO);
			i++;
		}
	}
}

static void	finish_print(void)
{
	write(STDERR_FILENO, "\n", 1);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	ft_putstr_fd(g_input->input, STDERR_FILENO);
	return_cursor();
	null_autocmpl(1);
}

void		print_array(char **arr)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	g_input->autocompl.save_curs = g_input->curs_pos;
	go_end_pos();
	write(STDERR_FILENO, "\n", 1);
	while (arr[i])
	{
		len += ft_strlen(arr[i]);
		if (len >= g_input->ws.ws_col)
		{
			len = ft_strlen(arr[i]);
			ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
			ft_putstr_fd(tgetstr("cr", NULL), STDERR_FILENO);
		}
		ft_putstr_fd(arr[i], STDERR_FILENO);
		len += 3;
		if (len < g_input->ws.ws_col)
			ft_putstr_fd("   ", STDERR_FILENO);
		i++;
	}
	finish_print();
}

void		change_input(char **str, char *key)
{
	int		i;
	DIR		*dir;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tmp = ft_strfjoin(g_input->autocompl.path, "/");
	g_input->autocompl.path = ft_strjoin(tmp, str[0]);
	dir = opendir(g_input->autocompl.path);
	if (dir)
	{
		closedir(dir);
		str[0] = ft_strfjoin(str[0], "/");
	}
	if (key)
	{
		while (str[0][i] && key[i] && str[0][i] == key[i])
			i++;
	}
	print(str[0] + i);
	null_autocmpl(1);
}
