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
	}
	if (g_input)
	{
		ft_free(g_input->prompt);
		free_int_arr();
		free(g_input);
	}
	shell = NULL;
	g_hist = NULL;
	g_input = NULL;
}

void		ft_free(char *str)
{
	if (str && *str)
		free(str);
	str = NULL;
}

void		free_int_arr(void)
{
	if (g_input->multiline.start_if_line)
		free(g_input->multiline.start_if_line);
	g_input->multiline.start_if_line = NULL;
}

void		null_autocmpl(void)
{
	int		i;

	i = 0;
	if (g_input->autocompl.seach_res)
	{
		while (g_input->autocompl.seach_res[i])
		{
			free(g_input->autocompl.seach_res[i]);
			g_input->autocompl.seach_res[i] = NULL;
			i++;
		}
		free(g_input->autocompl.seach_res);
	}
	g_input->autocompl.seach_res = NULL;
	g_input->autocompl.amount = 0;
	g_input->autocompl.cmd = 0;
	g_input->autocompl.file = 0;
	g_input->autocompl.key_check = 0;
	g_input->autocompl.save_curs = 0;
	g_input->autocompl.tab_count = 0;
}
