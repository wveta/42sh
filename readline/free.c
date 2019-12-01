#include "readline.h"

void		ft_free(char *str)
{
	if (str && *str)
		free(str);
	str = NULL;
}

void		free_int_arr(void)
{
	free(g_input->multiline.start_if_line);
	g_input->multiline.start_if_line = NULL;
}

void		null_autocmpl(void)
{
	int		i;

	i = 0;
	if (g_input->autocompl.seach_res)
	{
		while (i < g_input->autocompl.amount && g_input->autocompl.seach_res[i])
		{
			free(g_input->autocompl.seach_res[i]);
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
