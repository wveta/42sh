/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:01:14 by thaley            #+#    #+#             */
/*   Updated: 2019/12/10 16:11:52 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		free_all(t_shell *shell)
{
	int		i;

	i = -1;
	if (shell)
	{
		ft_free(shell->term);
		free(shell);
	}
	if (g_hist)
	{
		while (g_hist->cmd[++i])
			ft_free(g_hist->cmd[i]);
		free(g_hist->cmd);
		ft_free(g_hist->path);
		free(g_hist);
		g_hist = NULL;
	}
	if (g_input)
	{
		ft_free(g_input->prompt);
		// free_int_arr();
		free(g_input);
	}
	shell = NULL;
	g_hist = NULL;
	g_input = NULL;
}

void		ft_free(char *str)
{
	if (str != NULL)
		free(str);
}

// void		free_int_arr(void)
// {
// 	if (g_input->multiline.start_of_line)
// 		free(g_input->multiline.start_of_line);
// 	g_input->multiline.start_of_line = NULL;
// }

void		null_autocmpl(int time)
{
	int		i;

	i = 0;
	if (g_input->autocompl.seach_res && time)
	{
		while (g_input->autocompl.seach_res[i])
		{
			free(g_input->autocompl.seach_res[i]);
			g_input->autocompl.seach_res[i] = NULL;
			i++;
		}
		free(g_input->autocompl.seach_res);
	}
	if (time)
		ft_free(g_input->autocompl.path);
	g_input->autocompl.path = NULL;
	g_input->autocompl.seach_res = NULL;
	g_input->autocompl.amount = 0;
	g_input->autocompl.cmd = 0;
	g_input->autocompl.file = 0;
	g_input->autocompl.key_check = 0;
	g_input->autocompl.save_curs = 0;
	g_input->autocompl.tab_count = 0;
}

void		null_multiline(void)
{
	g_input->multiline.num_of_lines = 0;
	g_input->multiline.pos = 0;
	g_input->multiline.start_of_line = 0;
}
