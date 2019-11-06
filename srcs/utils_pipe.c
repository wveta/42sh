/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/11/06 14:59:06 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_arr_fd(int code, int fd0[2], int fd1[2])
{
	if (code == 1 || code == 2)
	{
		fd1[0] = -1;
		fd1[1] = -1;
	}
	if (code == 0 || code == 2)
	{
		fd0[0] = -1;
		fd0[1] = -1;
	}
}

void	ft_set_cmd_pipe(int code, t_cmdlist *cur_cmd, int fd0[2], int fd1[2])
{
	if (code == 0)
	{
		cur_cmd->fd_pipe_in[0] = fd0[0];
		cur_cmd->fd_pipe_in[1] = fd0[1];
	}
	else if (code == 1)
	{
		cur_cmd->fd_pipe_in[0] = -1;
		cur_cmd->fd_pipe_in[1] = -1;
	}
	else if (code == 2)
	{
		cur_cmd->fd_pipe_in[0] = fd1[0];
		cur_cmd->fd_pipe_in[1] = fd1[1];
	}
	else
		ft_set_cmd_pipe_out(code, cur_cmd, fd0, fd1);
}

void	ft_set_cmd_pipe_out(int code, t_cmdlist *cur_cmd,
		int fd0[2], int fd1[2])
{
	if (code == 3)
	{
		cur_cmd->fd_pipe_out[0] = fd1[0];
		cur_cmd->fd_pipe_out[1] = fd1[1];
	}
	else if (code == 4)
	{
		cur_cmd->fd_pipe_out[0] = -1;
		cur_cmd->fd_pipe_out[1] = -1;
	}
	else if (code == 5)
	{
		cur_cmd->fd_pipe_out[0] = fd0[0];
		cur_cmd->fd_pipe_out[1] = fd0[1];
	}
}

void	ft_pipe_dup_ch_in(t_cmdlist *cur_cmd)
{
//	
	char	*tmp;
	char 	*tmp2;
	char	*nr;
//
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nPIPE IN subshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, "cur_cmd->nr = ");
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, ft_putfnbr(cur_cmd->nr, nr));
		ft_rec_log(tmp);
		free(tmp);
		free(nr);
			
	if (g_subshell > 0 && cur_cmd->nr == 1)
	{
		ft_rec_log("\nPIPE IN OK");
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nPIPE IN OK subshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		tmp2 = ft_strjoin(tmp2, "g_subsh_in0 = ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_in0, nr));
		tmp2 = ft_strjoin(tmp2, " ");
		tmp2 = ft_strjoin(tmp2, "g_subsh_in1 = ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_in1, nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);
		
		cur_cmd->fd_pipe_in[0] = g_subsh_in0;
		cur_cmd->fd_pipe_in[1] = g_subsh_in1;
	}
	if (cur_cmd->fd_pipe_in[0] != -1 && cur_cmd->fd_pipe_in[0] != 0)
	{
		
		if (dup2(cur_cmd->fd_pipe_in[0], 0) == -1)
		{
			ft_print_msg(" : Error relink to STDIN: ", "DUP2");
			exit(0);
		}
		//

		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "relink STDIN cur_cmd->fd_pipe_in[0] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(cur_cmd->fd_pipe_in[0], nr));
		ft_rec_log(tmp2);


		close(cur_cmd->fd_pipe_in[0]);
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "CLOSE cur_cmd->fd_pipe_in[0] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(cur_cmd->fd_pipe_in[0], nr));
		ft_rec_log(tmp2);

		if (cur_cmd->fd_pipe_in[1] != -1)
		{
			close(cur_cmd->fd_pipe_in[1]);
					tmp2[0] = '\0';
			tmp2 = ft_strjoin(tmp2, tmp);
			tmp2 = ft_strjoin(tmp2, " ");
			nr[0] = '\0';
			tmp2 = ft_strjoin(tmp2, "CLOSE cur_cmd->fd_pipe_in[1] = ");
			tmp2 = ft_strjoin(tmp2, ft_putfnbr(cur_cmd->fd_pipe_in[1], nr));
			ft_rec_log(tmp2);
		}

		free(tmp);
		free(tmp2);
		free(nr);
	}
}

void	ft_pipe_dup_ch_out(t_cmdlist *cur_cmd)
{
	//	
	char	*tmp;
	char 	*tmp2;
	char	*nr;
//
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nPIPE OUT  subshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, "cur_cmd->nr = ");
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, ft_putfnbr(cur_cmd->nr, nr));
		ft_rec_log(tmp);
		free(tmp);
		free(nr);
	if (g_subshell > 0 && (!(cur_cmd->next)))
	{

		ft_rec_log("\nPIPE OUT OK");
		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nPIPE OUT OK subshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		tmp2 = ft_strjoin(tmp2, "g_subsh_out0 = ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_out0, nr));
		tmp2 = ft_strjoin(tmp2, " ");
		tmp2 = ft_strjoin(tmp2, "g_subsh_out1 = ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(g_subsh_out1, nr));
		ft_rec_log(tmp2);
		free(tmp);
		free(tmp2);
		free(nr);
		

		
		cur_cmd->fd_pipe_out[0] = g_subsh_out0;
		cur_cmd->fd_pipe_out[1] = g_subsh_out1;
	}
	if (cur_cmd->fd_pipe_out[1] != -1 && cur_cmd->fd_pipe_out[1] != 1)
	{
		if (dup2(cur_cmd->fd_pipe_out[1], 1) == -1)
		{
			ft_print_msg(" : Error relink to STDOUT: ", "DUP2");
			exit(0);
		}
		//

		tmp2 = ft_strnew(1000);
		tmp = ft_strnew(1000);
		tmp[0] = '\0';
		nr = ft_strnew(1000);
		nr[0] = '\0';
		tmp = ft_strjoin(tmp, "\nsubshell = ");
		tmp = ft_strjoin(tmp, ft_putfnbr(g_subshell, nr));
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, cur_cmd->avcmd[0]);
		tmp = ft_strjoin(tmp, " ");
		tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "relink STDOUT cur_cmd->fd_pipe_out[1] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(cur_cmd->fd_pipe_out[1], nr));
		ft_rec_log(tmp2);

		close(cur_cmd->fd_pipe_out[1]);
				tmp2[0] = '\0';
		tmp2 = ft_strjoin(tmp2, tmp);
		tmp2 = ft_strjoin(tmp2, " ");
		nr[0] = '\0';
		tmp2 = ft_strjoin(tmp2, "CLOSE cur_cmd->fd_pipe_out[1] = ");
		tmp2 = ft_strjoin(tmp2, ft_putfnbr(cur_cmd->fd_pipe_out[1], nr));
		ft_rec_log(tmp2);

		if (cur_cmd->fd_pipe_out[0] != -1)
		{
			close(cur_cmd->fd_pipe_out[0]);
				tmp2[0] = '\0';
			tmp2 = ft_strjoin(tmp2, tmp);
			tmp2 = ft_strjoin(tmp2, " ");
			nr[0] = '\0';
			tmp2 = ft_strjoin(tmp2, "CLOSE cur_cmd->fd_pipe_out[0] = ");
			tmp2 = ft_strjoin(tmp2, ft_putfnbr(cur_cmd->fd_pipe_out[0], nr));
			ft_rec_log(tmp2);
		}


		free(tmp);
		free(tmp2);
		free(nr);
	}
}
