# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wveta <wveta@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 13:59:52 by thaley            #+#    #+#              #
#    Updated: 2019/11/13 18:31:59 by udraugr-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= readline.a
FILES		:= autocomplition cursor history init\
			input match_key move_char move_line\
			readline signal ft_free ascii_sort\
			cut_paste get_next_line print_tab\
			search_tab copy space recurs_search\
			update_hist history_back_n ft_exit insert_char\
			delete parsepath mall_check

SRC			:= $(patsubst %, %.c, $(FILES))
OBJ			:= $(patsubst %, %.o, $(FILES))

INCL_DIR	:= ../libft

FLAGS		:= -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@printf "\r\033[32;1mCreate $(NAME)!                                      \n\033[0m"
	@printf "\033[?25h"

%.o: %.c $(INCL_DIR)/libft.h
	@printf "\033[?25l"
	@gcc $(FLAGS) -I$(INCL_DIR) -o $@ -c $<
	@printf "\r\033[34;1mNow compiling $@!                                    \033[0m"

so:
	@gcc -shared -o readline.so -fPIC *.c -I ../libft

clean:
	@/bin/rm -f $(OBJ)
	@printf "\r\033[31mDell all o files!                                      \n\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\r\033[31;1mDell $(NAME)!                                        \n\033[0m"

re: fclean all
