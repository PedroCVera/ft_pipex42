# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcoimbra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 11:39:38 by pcoimbra          #+#    #+#              #
#    Updated: 2022/05/18 16:13:02 by pcoimbra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

HEAD = includes

LIBFT = -lft -L libft

NAME		= pipex

#NAME_B		= checker

INCLUDE		= get_next_line/gnl/get_next_line.h so_long.h

SRCS		= get_next_line/gnl/get_next_line.c get_next_line/gnl/get_next_line_utils.c \
				src/parsing.c src/pipex.c src/childwork.c src/shitdealer.c
#				srcs/cmds.c srcs/pipex_pars.c src/shitdealer.c srcs/ft_pipex.c

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEAD}

${NAME}: ${OBJS}
	make bonus -C libft/
	${CC} ${CFLAGS} -lft $^ -I ${HEAD} -o $@ -L ./libft

all: ${NAME}

clean:
	${RM} ${OBJS}
	make clean -C libft/

fclean: clean
	${RM} ${NAME}
	make fclean -C libft/

re:	fclean all

.PHONY: all fclean clean re
