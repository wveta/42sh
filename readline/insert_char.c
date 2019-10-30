/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:31:19 by thaley            #+#    #+#             */
/*   Updated: 2019/10/23 19:54:15 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		insert_char_color(char c, int all)
{
	int		i;
	int		first;

	first = 1;
	i = g_input->cursor_pos;
	if (g_input->input_len + 1 >= MAX_CMDS)
		return ;
	ft_memmove(g_input->input + g_input->cursor_pos + 1, g_input->input
			+ g_input->cursor_pos, MAX_CMDS - g_input->cursor_pos - 1);
	g_input->input[g_input->cursor_pos] = c;
	ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
	while (i <= g_input->input_len)
	{
		if (first || all)
		{
			ft_putstr_fd("\033[7m", STDIN_FILENO);
			first = 0;
		}
		write(1, &g_input->input[i], 1);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
		i++;
	}
	g_input->input_len++;
	g_input->cursor_pos++;
}

void		insert_char(char *c)
{
	int		i;
	int		save_curs;
	char	*tmp;
	char	buf[MAX_CMDS];

	i = 0;
	save_curs = 0;
	ft_bzero(buf, MAX_CMDS);
	if (c[0] == '\0')
		return ;
	if (g_input->input_len != g_input->cursor_pos - g_input->prompt_len)
	{
		save_curs = g_input->cursor_pos + 1;
		ft_strncpy(buf, g_input->input, g_input->cursor_pos - g_input->prompt_len);
		tmp = ft_strjoin(c, g_input->input + (g_input->cursor_pos - g_input->prompt_len));
		ft_bzero(g_input->input, MAX_CMDS);
		ft_strcpy(g_input->input, buf);
		ft_strcat(g_input->input, tmp);
	}
	else
	{
		ft_strcat(g_input->input, c);
		tmp = ft_strdup(c);
	}
	g_input->input_len = ft_strlen(g_input->input);
	g_input->cursor_pos = g_input->input_len + g_input->prompt_len;
	ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
	while (tmp[i])
		ft_putchar_fd(tmp[i++], STDOUT_FILENO);
	if (g_input->cursor_pos % g_input->ws.ws_col == 0)
		ft_putstr_fd(tgetstr("do", NULL), STDIN_FILENO);
	if (save_curs)
	{
		while (--i > 0)
			ft_move_left();
	}
	free(tmp);
	tmp = NULL;
}
