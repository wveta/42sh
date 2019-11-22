/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:43:17 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/22 11:17:14 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/arithmetic.h"
#include <stdio.h>

/*int					main(int argc, char **argv)
{
	t_list			*lexem;
	int32_t			result;

	if (argc != 2)
		return (1);
	else
	{
		result = 0;
		g_error_arithmetic = 0;
		lexem = parser_str(argv[1]);
		if (g_error_arithmetic)
		{
			printf("42sh: %s : %s\n", argv[1], g_error_arithmetic);
			ft_strdel(&g_error_arithmetic);
			return (1);
		}
		for (t_list *begin = lexem; begin; begin = begin->next)
		{
			char *type;
			if (begin->content_size == VAR)
				type = "Variable";
			else if (begin->content_size == NUMB)
				type = "Number";
			else
				type = "Operator";	
			printf("{%s}\t", type);
			if (begin->content_size == VAR)
			{
				printf("Name: [%s], value: [%d]\n", ((t_var *)begin->content)->name, ((t_var *)begin->content)->value);
			}
			else if (begin->content_size == NUMB)
			{
				printf("value: [%d]\n", ((t_numb *)begin->content)->numb);
			}
			else
			{
				if (((t_oper *)begin->content)->id == INCREMENT)
					printf("INCREMENT ++\n");
				else if (((t_oper *)begin->content)->id == DECREMENT)
					printf("DECREMENT --\n");
				else if (((t_oper *)begin->content)->id == PLUS)
					printf("PLUS +\n");
				else if (((t_oper *)begin->content)->id == MINUS)
					printf("MINUS -\n");
				else if (((t_oper *)begin->content)->id == MULTIPLICATION)
					printf("MULTIPLICATION *\n");
				else if (((t_oper *)begin->content)->id == DIVISION)
					printf("DIVISION /\n");
				else if (((t_oper *)begin->content)->id == MODULE)
					printf("MODULE %% --\n");
				else if (((t_oper *)begin->content)->id == LE)
					printf("LE <=\n");
				else if (((t_oper *)begin->content)->id == GE)
					printf("GE >=\n");
				else if (((t_oper *)begin->content)->id == LESSER)
					printf("LESSER <\n");
				else if (((t_oper *)begin->content)->id == GREATER)
					printf("GREATER >\n");
				else if (((t_oper *)begin->content)->id == EQUAL)
					printf("EQUAL ==\n");
				else if (((t_oper *)begin->content)->id == NOT_EQUAL)
					printf("NOT_EQUAL !=\n");
				else if (((t_oper *)begin->content)->id == AND)
					printf("AND &&\n");
				else if (((t_oper *)begin->content)->id == OR)
					printf("OR ||\n");
				else if (((t_oper *)begin->content)->id == LBRACE)
					printf("LBRACE (\n");
				else if (((t_oper *)begin->content)->id == RBRACE)
					printf("RBRACE )\n");
			}
		}
		lexem = parser_str(argv[1]);
		if (!g_error_arithmetic)
		{
			g_lexem = lexem;
			result = expr();
			if (!g_error_arithmetic && !g_lexem)
			{
				ft_putnbr(result);
				write(1, "\n", 1);
			}
			else
			{
				if (!g_error_arithmetic && g_lexem)
					syntax_error_found();
				printf("42sh: %s : %s\n", argv[1], g_error_arithmetic);
				ft_strdel(&g_error_arithmetic);
			}
			lst_del(&lexem, destroy_lexem);
		}
	}
	return (0);
}*/

static void			ft_print_error_message_arithmetic(char *str)
{
	char			*event;
	
	event = ft_strjoin(" : ", str);
	event = ft_strfjoin(event, " : ");
	ft_print_msg(event, g_error_arithmetic);
	ft_strdel(&event);
	ft_strdel(&g_error_arithmetic);
}

char				*calculator(char *str)
{
	t_list			*lexem;
	int32_t			result;
	char			*ans;

	result = 0;
	g_error_arithmetic = 0;
	g_lexem = 0;
	g_correct_values = 0;
	lexem = parser_str(str);
	ans = 0;
	if (g_error_arithmetic)
		ft_print_error_message_arithmetic(str);
	else
	{
		g_lexem = lexem;
		result = expr();
		if (!g_error_arithmetic && !g_lexem)
			ans = ft_itoa(result);
		else
		{
			if (!g_error_arithmetic && g_lexem)
				syntax_error_found();
			ft_print_error_message_arithmetic(str);
		}
	}
	lst_del(&lexem, destroy_lexem);
	return (ans);
}