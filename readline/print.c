/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:09:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/12 21:46:11 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			take_curs(void)
{
	int		curs;
	int		i;
	char	buf[20];

	i = 0;
	ft_bzero(buf, 20);
	ft_putstr_fd("\e[6n", STDIN_FILENO);
	read(STDIN_FILENO, &buf, 20);
	while (buf[i])
	{
		i++;
		if (buf[i - 1] == ';')
			break ;
	}
	curs = ft_atoi(buf + i);
	return (curs);
}

int			count_n(char *str)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1])
			n++;
		i++;
	}
	return (n);
}

char		*check_curs_pos(int *save_curs, char *buf, char *str, char *tmp)
{
	if (g_input->input_len != g_input->curs_pos - g_input->prompt_len)
	{
		ft_strncpy(buf, g_input->input, g_input->curs_pos\
					- g_input->prompt_len);
		if (str[0] != '\0')
		{
			tmp = ft_strjoin(str, g_input->input +\
			g_input->curs_pos - g_input->prompt_len);
			*save_curs = g_input->curs_pos + 1;
		}
		else
		{
			tmp = ft_strdup(g_input->input +\
			g_input->curs_pos - g_input->prompt_len);
			*save_curs = g_input->curs_pos;
		}
		ft_bzero(g_input->input, MAX_CMDS);
		ft_strcpy(g_input->input, buf);
		g_input->input_len = g_input->curs_pos - g_input->prompt_len;
	}
	else
		tmp = ft_strdup(str);
	return (tmp);
}

void		print_loop(char *tmp, int curs)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if ((tmp[i] == '\n' || ft_isprint(tmp[i]))\
			&& g_input->input_len < MAX_CMDS)
		{
			g_input->input[(g_input->curs_pos - g_input->prompt_len)] = tmp[i];
			g_input->curs_pos++;
			curs = take_curs();
			ft_putchar_fd(tmp[i], STDERR_FILENO);
			if (curs == g_input->ws.ws_col && tmp[i] != '\n')
				ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
			else if ((tmp[i] == '\n' && curs == g_input->ws.ws_col))
				ft_putstr_fd(tgetstr("do", NULL), STDERR_FILENO);
			g_input->input_len++;
		}
		if (g_input->input_len >= MAX_CMDS)
			ft_putchar_fd(tmp[i], STDERR_FILENO);
		i++;
	}
}

void		print(char *str)
{
	int		save_curs;
	int		curs;
	char	*tmp;
	char	buf[MAX_CMDS];

	tmp = NULL;
	save_curs = 0;
	ft_bzero(buf, MAX_CMDS);
	if (!str)
		return ;
	tmp = check_curs_pos(&save_curs, buf, str, tmp);
	curs = take_curs();
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	null_multiline();
	print_loop(tmp, curs);
	count_lines();
	if (!g_input->multiline.num_of_lines)
		null_multiline();
	if (save_curs > 0)
	{
		while (g_input->curs_pos > save_curs)
			move_left();
	}
	free(tmp);
}
