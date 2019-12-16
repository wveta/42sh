/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 19:44:22 by thaley            #+#    #+#             */
/*   Updated: 2019/12/16 19:53:11 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		ft_read_file(const int fd, char *buf, t_gnlist **list)
{
	char	*str;
	char	*str2;
	int		ret;

	ret = 0;
	str2 = (*list)->content;
	while ((str2) && ((ft_strchr(str2, '\n')) == NULL) &&
			(ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		str = ft_strjoin(str2, buf);
		free(str2);
		str2 = str;
	}
	(*list)->content = str2;
	return (ret);
}

static	void	ft_line_rec(char **line, t_gnlist **list, size_t len)
{
	char	*str;
	char	*tmp;

	str = (char *)((*list)->content);
	while ((str) && str[len] != '\n' && str[len] != '\0')
		len++;
	if (len == 0)
	{
		if (!(*line = ft_strnew(1)))
			return ;
	}
	else
	{
		tmp = ft_strsub(str, 0, len + 1);
		if (line && *line)
			*line = ft_strcpy(*line, tmp);
		else
			*line = ft_strdup(tmp);
		free(tmp);
	}
	if ((str) && str[len] == '\n' && str[len] != '\0')
		len++;
	str ? str = ft_strsub(str, len, ft_strlen(str) - len) : 0;
	free((*list)->content);
	(*list)->content = str;
}

static t_gnlist	*ft_new_list(int fd, t_gnlist *list)
{
	t_gnlist	*new_list;

	if (fd < 0 && list)
	{
		if (list->content)
			free(list->content);
		free(list);
		return (0);
	}
	if (!(new_list = (t_gnlist *)malloc(sizeof(t_gnlist))))
		return (NULL);
	new_list->content = ft_strnew(1);
	new_list->content_size = fd;
	new_list->next = NULL;
	return (new_list);
}

static int		ft_result(int ret, t_gnlist **tmp, char *buf, char **line)
{
	size_t	len;

	len = 0;
	if (ret == 0 && (!((*tmp)->content) || (ft_strlen((*tmp)->content) == 0)))
	{
		if (!((*tmp)->content) || (ft_strlen((*tmp)->content) == 0))
		{
			free((*tmp)->content);
			(*tmp)->content = ft_strnew(1);
		}
		return (0);
	}
	else
	{
		ft_line_rec(line, tmp, len);
		buf[0] = '\0';
		return (1);
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_gnlist	*list;
	t_gnlist		*tmp;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 && list)
		return (0);
	if (fd < 0 || !line || (read(fd, buf, 0)))
		return (-1);
	if (!list)
	{
		if (!(list = ft_new_list(fd, NULL)))
			return (-1);
	}
	tmp = list;
	while (tmp->content_size != fd)
	{
		if (tmp->next == NULL)
			tmp->next = ft_new_list(fd, NULL);
		tmp = tmp->next;
	}
	ret = ft_read_file(fd, buf, &tmp);
	return ((ft_result(ret, &tmp, buf, line)));
}
