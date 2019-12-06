/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:47:27 by thaley            #+#    #+#             */
/*   Updated: 2019/12/06 20:52:28 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		add_to_hist(void)
{
	int		len;
	int		fd;

	len = 0;
	len = g_input->input_len + 2;
	if (g_hist->amount == 100)
		g_hist->cmd = remake_hist();
	g_hist->cmd[g_hist->amount] = ft_strnew(len);
	g_hist->cmd[g_hist->amount] = ft_strcpy(g_hist->cmd[g_hist->amount], g_input->input);
	g_hist->cmd[g_hist->amount][len - 2] = 7;
	g_hist->cmd[g_hist->amount][len - 1] = '\n';
	g_hist->amount++;
	g_hist->pos = g_hist->amount;
	g_hist->cmd[g_hist->amount] = NULL;
	if ((fd = open(g_hist->path, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)) <= 0)
		return ;
	write(fd, g_hist->cmd[g_hist->amount - 1], ft_strlen(g_hist->cmd[g_hist->amount - 1]));
	close(fd);
}

char		*return_func(char *str, char *input, t_shell *shell)
{
	int		len;
	char	*tmp;

	len = 0;
	if (str[0] == ENTER && !str[1] && !g_input->heredoc && g_input->input_len > 0)
		add_to_hist();
	if (str[0] == 4 && !str[1] && g_input->heredoc)
		tmp = ft_strdup(str);
	else if (str[0] == 4 && !str[1])
		tmp = ft_strdup("exit");
	else
	{
		tmp = ft_strdup(input);
		len = -1;
		while (tmp[++len] && tmp[len + 1])
		{
			if ((tmp[len] == '\\') && (tmp[len + 1] == '\n'))
			{
				if (tmp[len + 2])
				{
					ft_strcpy(tmp + len, tmp + len + 2);
					len = len - 2;
				}
				else
				{
					tmp[len] = '\0';
					len--;
				}
			}	
			else if (tmp[len] == '\n')
			{
				ft_strcpy(tmp + len, tmp + len + 1);
				len--;
			}
		}
	}
	tcsetattr(0, TCSADRAIN, &shell->old_param);
	return (tmp);
}

//remake

void		mall_check(void)
{
	ft_putstr_fd("ERROR: Cannot allocate memory.", STDERR_FILENO);
	return_func("\0", "exit", NULL);
}
