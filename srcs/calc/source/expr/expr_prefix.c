/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_prefix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:12:39 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/19 11:06:21 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arithmetic.h"

int32_t					expr_prefix(void)
{
	int32_t				ans;
	int32_t				type;
	
	if (g_lexem && g_lexem->content_size == OPER
			&&
			(
				((t_oper *)g_lexem->content)->id == INCREMENT
				|| ((t_oper *)g_lexem->content)->id == DECREMENT
			)
			&& g_lexem->next && g_lexem->next->content_size == VAR
		)
	{
		type = ((t_oper *)g_lexem->content)->id;
		g_lexem = g_lexem->next;
		ans = (type == INCREMENT) ?
			++((t_var *)g_lexem->content)->value
			: --((t_var *)g_lexem->content)->value;
		g_lexem = g_lexem->next;
		return (ans);
	}
	ans = expr_suffix();
	if (g_error_arithmetic)
		return (0);
	return (ans);
}