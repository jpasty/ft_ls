# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpasty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 17:26:06 by jpasty            #+#    #+#              #
#    Updated: 2020/03/05 17:26:17 by jpasty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_printf

DIR_FLOAT := float/
DIR_SRC := src/

SRC_MAIN 	:= 	ft_printf.c\
				format_parse.c\
				numeric_helpers.c\
				print_base.c\
				print_int.c\
				print_unsigned.c\
				print_symbolic.c\
				free.c\
				utils.c\
				assist.c\
				color.c

SRC_FLOAT 	:= 	print_float.c\
				sum.c\
				subtr.c\
				negs.c\
				mult.c\
				prec.c\
				prec2.c


SRCS_FT_PRINTF := $(SRC_MAIN) $(SRC_FLOAT)
DIRS_FT_PRINTF := $(DIR_SRC) $(addprefix $(DIR_SRC), $(DIR_MAIN) $(DIR_FLOAT))