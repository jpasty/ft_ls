# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 16:45:56 by jpasty            #+#    #+#              #
#    Updated: 2020/06/04 18:30:20 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./ft_printf/Makefile

NAME 			:= libft.a
FLAGS 			:= -Wextra -Werror -Wall
CC 				:= gcc
REMOVE 			:= /bin/rm -rf
DIR_INCLUDE 	:= ./include
H_LIBFT			:= libft.h
H_FT_PRINTF		:= ft_printf.h
HEADERS			:= $(H_LIBFT) $(H_FT_PRINTF)
DIR_BIN 		:= bin/
DIR_LIBFT		:= .
DIR_FT_PRINTF	:= ft_printf/

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	   ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
	   ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
	   ft_memccpy.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memdel.c \
	   ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
	   ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
	   ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strcspn.c \
	   ft_strdel.c ft_strdup.c ft_strequ.c ft_strnew.c ft_strnstr.c \
	   ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
	   ft_tolower.c ft_toupper.c ft_striter.c ft_striteri.c ft_strjoin.c \
	   ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	   ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_swap.c ft_error.c \
	   get_next_line.c ft_free_strsplit.c

SRCS 			:= $(SRC) $(SRCS_FT_PRINTF)

DIRS_FT_PRINTF	:= $(addprefix $(DIR_FT_PRINTF), $(DIRS_FT_PRINTF))
DIRS_SRC		:= $(DIRS_FT_PRINTF) $(DIR_LIBFT)

OBJS			:= $(SRCS:.c=.o)
OBJS_BIN		:= $(addprefix $(DIR_BIN), $(OBJS))

vpath %.c $(DIRS_SRC)
vpath %.h $(DIR_INCLUDE)
vpath %.o $(DIR_BIN)

all: $(NAME)

$(NAME): $(OBJS)
	ar crus $@ $(OBJS_BIN)

$(OBJS):%.o: %.c $(HEADERS) | $(DIR_BIN)
	$(CC) $(FLAGS) -c $< -o $(DIR_BIN)$@ $(addprefix -I, $(DIR_INCLUDE)) -pipe

$(DIR_BIN):
	mkdir -p $@

clean:
	$(REMOVE) $(OBJS)
	$(REMOVE) $(DIR_BIN)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY:	clean fclean re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) clean fclean re
