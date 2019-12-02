/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_str_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/12/02 23:23:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "calc/include/arithmetic.h"

void	ft_cacl_test_b(int *br_flag, int *br_count, int i, char *str)
{
	if ((*br_flag == 0 || *br_flag == 1) &&
	str[i] == '(' && (i == 0 || ft_strchr(" ;|&$", str[i - 1])))
	{
		*br_flag = 1;
		*br_count = *br_count + 1;
	}
	else if (*br_flag == 1 && str[i] == '(')
		*br_count = *br_count + 1;
	else if ((*br_flag == 0 || *br_flag == 2) &&
	str[i] == '{' && (i == 0 || ft_strchr(" ;|&", str[i - 1])))
	{
		*br_flag = 2;
		*br_count = *br_count + 1;
	}
	else if (*br_flag == 1 && str[i] == '{')
		*br_count = *br_count + 1;
}

void	ft_calc_test_q(int *qflag, char *str, int i, int *b_sl)
{
	if ((*qflag == 2 && str[i] == '\'') && (i == 0 || *b_sl == 0))
		*qflag = 0;
	else if (*qflag == 0 && str[i] == '\'' && (i == 0 || *b_sl == 0))
		*qflag = 2;
}
