/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:42:54 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/02 10:39:17 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char			*ft_error_terminate(char *error_mesage,
											int open_fd, char **str_for_free)
{
	ft_print_msg(": Take_alias: ", error_mesage);
	if (open_fd != -1)
		close(open_fd);
	if (str_for_free)
		ft_strdel(str_for_free);
	return (0);
}

char				*ft_read_alias(void)
{
	int				fd;
	int				read_bytes;
	char			*all_alias;
	char			*old_all_alias;
	char			buffer[4096];

	if ((fd = open("/Users/udraugr-/.alias_42", O_CREAT | O_RDONLY, 0x1FF))
			== -1)
		return (ft_error_terminate("Can't open alias file!", -1, 0));
	if ((all_alias = ft_strnew(0)) == NULL)
	{
		return (ft_error_terminate("Malloc can't allocate memory!",
														fd, 0));
	}
	while ((read_bytes = read(fd, buffer, 4095)) > 0)
	{
		buffer[read_bytes] = '\0';
		old_all_alias = all_alias;
		if ((all_alias = ft_strjoin(all_alias, buffer)) == NULL)
		{
			return (ft_error_terminate("Malloc can't allocate memory!",
														fd, &old_all_alias));
		}
		ft_strdel(&old_all_alias);
	}
	close(fd);
	if (read_bytes == -1)
	{
		return (ft_error_terminate("'Read' can't read the file!",
														-1, &all_alias));
	}
	return (all_alias);
}
