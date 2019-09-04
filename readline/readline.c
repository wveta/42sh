/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 17:44:03 by thaley            #+#    #+#             */
/*   Updated: 2019/08/29 20:16:51 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** check standart file stream with term
*/

void			open_fd(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)\
		|| !isatty(STDERR_FILENO))
		exit(EXIT_FAILURE);
}

/*
** main for readline
*/

char			*read_line(char *prompt)
{
	t_shell			*shell;
	char			*ret;

	shell = NULL;
	init_input(prompt);
	shell = init_term(shell);
	g_input->cursor = get_cursor_pos();
	if (g_input->cursor.row == 0)
		return (NULL);
	if (g_input->cursor.col != 1)
		write(1, "\n", 1);
	ft_putstr_fd(prompt, STDIN_FILENO);
	g_input->cursor = get_cursor_pos();
	g_input->save_row = g_input->cursor.row;
	g_input->save_col = g_input->cursor.col;
	g_hist->cursor = 0;
	if (g_input->head != '\0' && g_input->head != '\n')
		insert_char(&g_input->head);
	ret = init_loop(shell);
	update_cursor();
	history_return_n(ret);
	write(1, "\n", 1);
	free_struct(&shell);
	return (ret);
}
