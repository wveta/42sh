# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 11:29:36 by udraugr-          #+#    #+#              #
#    Updated: 2019/11/19 11:22:33 by udraugr-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	calculator

SRC_DIR	:=	source

PARS_DIR:=	parser
SRC_PARS:=	\
			lex_numb.c\
			lex_operator.c\
			lex_variable.c\
			lexem_create.c\
			lexem_destroy.c\
			parser.c\
			check_increment_decrement.c\
			fts_lst.c
SRC_PARS:= $(addprefix $(PARS_DIR)/, $(SRC_PARS))

EXPR_DIR:=	expr
SRC_EXPR:=	\
			expr.c\
			expr_additive.c\
			expr_and.c\
			expr_barckets.c\
			expr_equal.c\
			expr_multiplicativ.c\
			expr_or.c\
			expr_prefix.c\
			expr_relat_op.c\
			expr_return_value.c\
			expr_suffix.c\
			expr_unar.c\
			syntax_error_found.c
			
SRC_EXPR:= $(addprefix $(EXPR_DIR)/, $(SRC_EXPR))

SRC		:= $(SRC_PARS) $(SRC_EXPR) main.c

OBJ_DIR	:=	object
OBJ		:=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

SUB_DIR :=	$(OBJ_DIR)\
			$(OBJ_DIR)/$(EXPR_DIR)\
			$(OBJ_DIR)/$(PARS_DIR)

INCL_DIR:=	include
INCLUDE	:=	-I$(INCL_DIR)
HEADER	:=	$(INCL_DIR)/arithmetic.h

LIB		:= -L libft -lft

FLAGS	:=	-g -Wall -Wextra -Werror

.PHONY:		all clean fclean re re_compile_libft vlg


all: $(NAME)

re_compile_libft:
	@make -C libft

$(NAME): re_compile_libft $(SUB_DIR) $(OBJ)
	@gcc $(FLAGS) $(INCLUDE) -o $(NAME) $(OBJ) $(LIB)
	@printf "\033[32;1m\rCrete $(NAME)!                                              \n\033[0m"
	@printf "\033[?25h"

$(SUB_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@printf "\033[?25l"
	@printf "\033[34;1m\rNow compiling $<!                                            \033[0m"
	@gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	@printf "\033[31m\rDell all objects!                                              \n\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\033[31;1m\rDell $(NAME)!                                                \n\033[0m"

vg:
	@valgrind --leak-check=full ./$(NAME) "1 + 2 + i++ - 4 * ++i / --j && y >= u-- || i != j || i == i"

re: fclean all