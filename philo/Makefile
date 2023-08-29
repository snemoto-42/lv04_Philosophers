# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 12:22:20 by snemoto           #+#    #+#              #
#    Updated: 2023/08/29 12:57:49 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Variables																	   #
# **************************************************************************** #

NAME	= philo
SRCS	= $(shell echo *.c)
OBJDIR	= obj/
OBJS	= $(SRCS:%.c=$(OBJDIR)%.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
RMD		= rm -rf

# **************************************************************************** #
# General Rules																   #
# **************************************************************************** #

all:	$(OBJDIR) $(NAME)

$(OBJDIR):
		mkdir -p obj

$(OBJDIR)%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		${RMD} $(OBJDIR)

fclean:	clean
		${RM} ${NAME}

re:		fclean all

bonus:	all

.PHONY: all clean fclean re bonus
