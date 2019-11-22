/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:28:05 by wveta             #+#    #+#             */
/*   Updated: 2019/11/22 18:10:17 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst && *alst && del)
	{
		while ((*alst)->next)
		{
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = (*alst)->next;
		}
		ft_lstdelone(&(*alst), del);
	}
}*/
void	ft_lstdel(t_list **lst, void (*f)(void *, size_t))
{
	t_list			*tmp;
	t_list			*del;

	if (!lst && !*lst)
		return ;
	tmp = *lst;
	*lst = 0;
	while (tmp)
	{
		if (tmp->content)
			f(tmp->content, tmp->content_size);
		tmp->content = 0;
		del = tmp;
		tmp = tmp->next;
		ft_memdel((void **)&del);
	}
}
