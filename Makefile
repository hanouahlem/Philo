# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 13:41:01 by ahbey             #+#    #+#              #
#    Updated: 2024/07/16 15:18:26 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  philo.c\
		parsing.c\
		utils.c\

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

LIBFT 	=	libft/libft.a

PRINTF  =   printf/libftprintf.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) 

$(LIBFT):
	make -C libft
	
$(PRINTF):
	make -C printf

%.o: %.c philo.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
		rm -f ${OBJS}
		make -C libft clean
		make -C printf clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		make -C printf fclean

re:		fclean all

.PHONY: all clean fclean re/