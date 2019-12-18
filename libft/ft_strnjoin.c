/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:47:55 by thaley            #+#    #+#             */
/*   Updated: 2019/12/18 03:17:02 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char *s1, char *s2, int len)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(ret = ft_strnew(len)))
		return (NULL);
	while (s1 && s1[i] && len)
	{
		ret[j++] = s1[i++];
		len--;
	}
	i = 0;
	while (s2 && s2[i] && len)
	{
		ret[j++] = s2[i++];
		len--;
	}
	ret[j] = '\0';
	return (ret);
}
