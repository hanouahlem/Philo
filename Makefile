# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 13:41:01 by ahbey             #+#    #+#              #
#    Updated: 2024/08/15 15:59:09 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  philo.c\
		parsing.c\
		utils.c\
		init_philo.c\
		init_mutex.c\
		routine.c\
		monito.c\

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo


all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c philo.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re/