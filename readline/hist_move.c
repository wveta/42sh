/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:49:20 by thaley            #+#    #+#             */
/*   Updated: 2019/12/06 13:34:42 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	input_from_hist(char *hist, int old)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(hist, 0, ft_strlen(hist) - 2);
	if (g_input->old_input[0] == '\0' && !g_input->old_in_check)
	{
		ft_strcpy(g_input->old_input, g_input->input);
		g_input->old_in_check = 1;
	}
	if (g_input->input_len > 0)
		ft_bzero(g_input->input, MAX_CMDS);
	go_home_pos();
	ft_putstr_fd(tgetstr("cd", NULL), STDERR_FILENO);
	g_input->input_len = 0;
	print(tmp);
	go_home_pos();
	while (g_input->curs_pos - g_input->prompt_len < g_input->input_len &&\
		g_input->input[g_input->curs_pos - g_input->prompt_len] != '\n')
		move_right();
	if (old)
	{
		ft_bzero(g_input->old_input, MAX_CMDS);
		g_input->old_in_check = 0;
	}
	free(tmp);
}

void		hist_move(int direction)
{
	if (g_input->multiline.pos)
		return ;
	if (direction && g_hist->pos < g_hist->amount)
		g_hist->pos++;
	else if (!direction && g_hist->pos > 0)
		g_hist->pos--;
	if (g_hist->pos == g_hist->amount && !g_hist->cmd[g_hist->pos])
		input_from_hist(g_input->old_input, 1);
	else
		input_from_hist(g_hist->cmd[g_hist->pos], 0);
}
