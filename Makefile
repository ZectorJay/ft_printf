# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:52:53 by hmickey           #+#    #+#              #
#    Updated: 2020/12/16 17:22:42 by hmickey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

PATH		=	./SRC/

INCLUDE		=	./ft_printf.h

SRCS		=	check_flags.c new_struct.c parse_decimal.c \
				parse_string.c ft_printf.c $(PATH)ft_atoi.c \
				$(PATH)ft_itoa.c $(PATH)ft_strlen.c $(PATH)ft_isdigit.c \
				$(PATH)ft_strchr.c $(PATH)ft_putstr_fd.c \
				$(PATH)ft_memset.c	parse_stars.c parse_xp.c \
				$(PATH)ft_isprint.c $(PATH)ft_strdup.c \
				$(PATH)ft_calloc.c $(PATH)ft_bzero.c

OBJS		= ${SRCS:.c=.o} 

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra

.c.o:		= ${CC} ${CFLAGS} -I${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME):		${OBJS} ${INCLUDE}
				ar rc ${NAME} ${OBJS}

all:			${NAME}

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all bonus clean fclean re
