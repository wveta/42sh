/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_suffix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 09:29:23 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/21 12:14:20 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					expr_suffix(void)
{
	int32_t				type;
	int32_t				ans;

	if (g_lexem && g_lexem->content_size == VAR
		&& g_lexem->next && g_lexem->next->content_size == OPER
		&& 
			(
				((t_oper *)g_lexem->next->content)->id == INCREMENT
				|| ((t_oper *)g_lexem->next->content)->id == DECREMENT
			)
		)
	{
		type = ((t_oper *)g_lexem->next->content)->id;
		ans = ((t_var *)g_lexem->content)->value;
		(type == INCREMENT) ? 
			((t_var *)g_lexem->content)->value++
			: ((t_var *)g_lexem->content)->value--;
		g_lexem = g_lexem->next->next;
		return (ans);
	}
	ans = expr_barckets();
	if (g_error_arithmetic)
		return (0);
	return (ans);
}