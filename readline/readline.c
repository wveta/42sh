/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:09:43 by thaley            #+#    #+#             */
/*   Updated: 2019/12/01 07:11:33 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	is_end_char(char c)
{
	if (c == 3 || c == SET_COLOR || c == SET_SIG || c == 12)
		return (1);
	else if (c == 4 && !g_input->input_len)
		return (1);
	else if (c == ENTER && !parse_quotes())
		return (1);
	return (0);
}

int			is_print(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] != 10 && str[i] < 32) || str[i] > 126)
			return (0);
		i++;
	}
	return (1);
}

char		*read_loop(t_shell *shell)
{
	char	c[20];
	
	g_cmd->jmp_code2 = setjmp(g_cmd->ebuf2);
	signal(SIGWINCH, ft_signal_win_size);
	while (1)
	{
		ft_bzero(c, 20);
		read(0, &c, 20);
		if (g_input->autocompl.tab_count == 1 && c[0] != TAB)
			null_autocmpl();
		if (match_key(c) || autocmp(c))
			continue ;
		else if (is_end_char(c[0]) && !c[1])
			return (return_func(c, g_input->input, shell));
		else
			print(c);
	}
}

char		*read_line(char *prompt)
{
	char	*ret;
	t_shell	*shell;

	ret = NULL;
	shell = NULL;
	init_input(prompt);
	shell = init_term(shell);
	ft_putstr_fd(prompt, STDERR_FILENO);
	ret = read_loop(shell);
	go_end_pos();
	// free_all();
	write(1, "\n", 1);
	return (ret);
}
