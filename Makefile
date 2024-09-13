# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 19:49:47 by dravaono          #+#    #+#              #
#    Updated: 2024/06/27 19:57:59 by dravaono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  main.c routine.c utils.c philo.c time.c eat_routine.c check.c\


OBJS = ${SRCS:.c=.o}
NAME = philosophers
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

all : ${NAME}

%.o: %.c
		${CC} ${CFLAGS} -o $@ -c $?

${NAME}:	${OBJS}	
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}
			
clean: 
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
