/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:46:12 by thaley            #+#    #+#             */
/*   Updated: 2019/11/27 14:40:18 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

// int			ft_isspace2(char st)
// {
// 	if (st == '\0' || st == ' ' || st == '\n' || st == '\t' ||
// 		st == '\r' || st == '\v' || st == '\f')
// 		return (1);
// 	return (0);
// }

// int			only_space(void)
// {
// 	int		i;

// 	i = 0;
// 	while (i < g_input->input_len)
// 	{
// 		if (ft_isspace2(g_input->input[i]))
// 			i++;
// 		else
// 			return (0);
// 	}
// 	return (1);
// }

int			parse_backslash(int start)
{
	int		count;

	count = 0;
	if (start < 0)
		return (-1);
	if (g_input->input[start] == '\\' && start > -1)
	{
		while (start > -1 && start != g_input->input_len
			&& g_input->input[start] == '\\')
		{
			start--;
			count++;
		}
	}
	return (count);
}

int			check_quotes(void)
{
	int 	i;

	i = 0;
	while (i < g_input->input_len)
	{
		if (g_input->start_quotes != i && g_input->quotes == '\0' && g_input->input[i] == '"' &&
		(i == 0 || g_input->input[i - 1] != '\\'))
		{
			g_input->quotes = '"';
			g_input->start_quotes = i;
		}
		else if (g_input->start_quotes != i && ((g_input->quotes == '"' && g_input->input[i] == '"') ||
			(g_input->quotes == '\'' && g_input->input[i] == '\'')) &&
		(i == 0 || g_input->input[i - 1] != '\\'))
		{
			g_input->quotes = '\0';
			g_input->start_quotes = 0;
		}
		else if (g_input->start_quotes != i && g_input->quotes == '\0' && g_input->input[i] == '\'' &&
		(i == 0 || g_input->input[i - 1] != '\\'))
		{
			g_input->quotes = '\'';
			g_input->start_quotes = i;
		}
		i++;
	}
	if (g_input->quotes == '\0')
	{
		g_input->start_quotes = 0;
		return (0);
	}
	return (1);
}

// void		check_double_quotes(int i)
// {
// 	int		check;

// 	check = 0;
// 	while (i < g_input->input_len)
// 	{
// 		if (g_input->input[i] == '\"' && (i > 0 && g_input->input[i - 1] != '\\'))
// 		{

// 			if (!g_input->quotes)
// 				g_input->quotes = g_input->input[i];
// 			else if (g_input->quotes == g_input->input[i])
// 				g_input->quotes = '\0';
// 		}
// 		else if ((g_input->input[i] == '\"' && (i > 0 && g_input->input[i - 1] == '\\')))
// 		{
// 			check = parse_backslash(i - 1);
// 			if (check % 2 == 0 && g_input->quotes)
// 				g_input->quotes = '\0';
// 			else if (check % 2 == 0 && !g_input->quotes)
// 				g_input->quotes = g_input->input[i];
// 		}
// 		i++;
// 	}
// }

int			parse_quotes(void)
{
	int				i;

	i = parse_backslash(g_input->input_len - 1);
	if (i % 2 != 0 && i > -1)
		return (1);
	if (check_quotes())
		return (1);
	return (0);
}
