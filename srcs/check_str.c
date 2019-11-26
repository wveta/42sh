/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/26 15:54:44 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_check_ekran(char *str, int pos)
{
	int i;
	int qflag;
	int br_count;
	int br_flag;

	i = 0;
	qflag = 0;
	br_count = 0;
	br_flag = 0;
	while (str && i < pos && str[i])
	{
		if (qflag == 0 && str[i] == '"' &&
		(i == 0 || str[i - 1] != '\\'))
			qflag = 1;
		else if (qflag == 0 && str[i] == '\'' &&
		(i == 0 || str[i - 1] != '\\'))
			qflag = 2;
		else if ((qflag == 1 && str[i] == '"' &&
		(i == 0 || str[i - 1] != '\\')) ||
				(qflag == 2 && str[i] == '\'' &&
		(i == 0 || str[i - 1] != '\\')))
			qflag = 0;
		else if (qflag == 0 && br_flag == 0 &&
				((str[i] == '(' && ((br_flag = 3))) ||
				(str[i] == '{' && ((br_flag = 4)))))
			br_count++;
		else if ((qflag == 0  && br_flag == 3 && str[i] == '(') ||
				(qflag == 0  && br_flag == 4 && str[i] == '{'))
			br_count++;
		else if ((qflag == 0  && br_flag == 3  && str[i] == ')') ||
				(qflag == 0  && br_flag == 4  && str[i] == '}'))
		{
			br_count--;
			if (br_count == 0)
				br_flag = 0;
		}
		i++;
	}
	if (qflag == 0 && br_flag == 0)
		return (0);
	return(qflag);
}