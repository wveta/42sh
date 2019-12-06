/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:15:41 by thaley            #+#    #+#             */
/*   Updated: 2019/12/06 13:21:41 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	prompt_len_color(char *prompt)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while(prompt[i])
	{
		if (prompt[i] == '\e' && (prompt[i + 1] && prompt[i + 1] == '[') \
			&& (prompt[i + 2] && ft_isdigit(prompt[i + 2])))
		{
			while (prompt[i] && (i == 0 || prompt[i - 1] != 'm'))
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void		null_all(void)
{
	ft_bzero(g_input->input, MAX_CMDS);
	ft_bzero(g_input->old_input, MAX_CMDS);
	ft_bzero(g_input->copy, MAX_CMDS);
	null_autocmpl();
	g_input->prompt_len = prompt_len_color(g_input->prompt);
	g_input->curs_pos = g_input->prompt_len;
	g_input->input_len = 0;
	g_input->heredoc = 0;
	g_input->multiline.num_of_lines = 0;
	g_input->multiline.pos = 0;
	g_input->multiline.start_if_line = NULL;
	g_input->quotes = '\0';
	g_input->start_quotes = -1;
	g_input->old_in_check = 0;
}

static void	open_fd(void)
{
	char	*tmp;
	int		fd1;
	int 	fd2;
	
	tmp = NULL;
	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	if (!isatty(STDOUT_FILENO))
	{
		tmp = ttyname(STDIN_FILENO);
		fd1 = open(tmp, O_RDWR | O_APPEND , S_IRUSR | S_IWUSR);
		if (fd1 == -1)
		{
			ft_print_msg(" : Error open STDOUT: ", tmp);
			exit(EXIT_FAILURE);
		}
	}
	if (!isatty(STDERR_FILENO))
	{
		tmp = ttyname(STDIN_FILENO);
		fd2 = open(tmp, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd2 == -1)
		{
			ft_print_msg(" : Error open STDERR: ", tmp);
			exit(EXIT_FAILURE);
		}	
	}
}

void		init_input(char *prompt)
{
	open_fd();
	if (!g_hist)
		create_history();
	if (!(g_input = (t_input *)malloc(sizeof(t_input))))
		mall_check() ;
	g_input->prompt = ft_strdup(prompt);
	if (!ft_strncmp(prompt, "heredoc", 7))
		g_input->heredoc = 1;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	ft_putstr_fd(tgetstr("bw", NULL), STDERR_FILENO);
	ft_putstr_fd(tgetstr("am", NULL), STDERR_FILENO);
	null_all();
}

t_shell		*init_term(t_shell *shell)
{
	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	if (!(shell->term = ft_get_env("TERM")))
		shell->term = ft_strdup("xterm-256color");
	if (tgetent(NULL, shell->term) == -1)
		return (NULL); //TODO: error msg
	if (tcgetattr(0, &shell->new_param) == -1)
		return (NULL);
	if (tcgetattr(0, &shell->old_param) == -1)
		return (NULL);
	shell->new_param.c_lflag &= ~(ICANON | ECHO | ISIG);
	shell->new_param.c_cc[VMIN] = 1;
	shell->new_param.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &shell->new_param) == -1)
		return (shell);
	return (shell);
}
