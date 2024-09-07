# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcatarin <gcatarin@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 17:26:30 by gcatarin          #+#    #+#              #
#    Updated: 2023/07/17 20:40:21 by gcatarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I./
RM				= rm -fr

NAME			= pipex
HEADER			= pipex.h

SOURCES			= srcs/ft_errors.c srcs/ft_split.c srcs/ft_childs.c \
					srcs/pipex.c srcs/ft_utils.c 

SOURCES_O		= $(SOURCES:srcs/%.c=objs/%.o)

all:		objs $(NAME)

$(NAME):		$(SOURCES_O)
	${CC} $(CFLAGS) -o ${NAME} $(SOURCES_O)

objs:
	mkdir -p objs

objs/%.o: srcs/%.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	$(RM) $(SOURCES_O)

fclean:			clean
	$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re