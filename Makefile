# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/03 22:41:31 by jpasty            #+#    #+#              #
#    Updated: 2020/06/07 21:40:06 by jpasty           ###   ########.ru        #
#                                                                              #
# **************************************************************************** #

NAME		:=	ft_ls
DIR_SRC		:=	srcs/
DIR_BIN		:=	bin/
DIR_INCLUDE :=	include/
DIR_LIBFT	:=	libft/
CC			:=	gcc
CFLAGS		:=	-g -Wextra -Werror -Wall
HEADERS		:=	libft.h ft_printf.h ft_getopt.h ft_ls.h
LIBFT		:=	libft.a
REMOVE		:=	rm -rf

SRC			:=	main.c collect_flags.c ft_getopt.c ft_getopt_long.c ft_ls.c \
				sort_list.c tools.c utils.c color_file.c print_output.c struct.c \
				print.c columns.c utils2.c

OBJS 		:= $(SRC:.c=.o)
LIBFT		:= $(addprefix $(DIR_LIBFT), $(LIBFT))

MAKE_LIBFT	:= make -C $(DIR_LIBFT)

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE)

all: make_lft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix $(DIR_BIN), $(OBJS)) $(LIBFT) -o $@

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $(CFLAGS) $< -o $(DIR_BIN)$@ -I $(DIR_INCLUDE)

$(DIR_BIN):
	mkdir -p $@

make_lft:
	$(MAKE_LIBFT)

clean:
	$(REMOVE) $(addprefix $(DIR_BIN), $(OBJS))
	$(REMOVE) $(DIR_BIN)
	$(MAKE_LIBFT) clean

fclean: clean
	$(REMOVE) $(NAME)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: clean fclean all re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) clean fclean re make_lft
