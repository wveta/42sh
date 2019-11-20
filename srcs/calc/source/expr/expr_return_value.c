/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_return_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:04:31 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/19 10:44:49 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arithmetic.h"

int32_t					expr_return_value(void)
{
	int32_t				result;

	if (!g_lexem
		|| (g_lexem->content_size != NUMB && g_lexem->content_size != VAR))
	{
		syntax_error_found();
		return (0);
	}
	else if (g_lexem->content_size == VAR)
		result = ((t_var *)g_lexem->content)->value;
	else
		result = ((t_numb *)g_lexem->content)->numb;
	g_lexem = g_lexem->next;
	return (result);
}