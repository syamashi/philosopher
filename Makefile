# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 12:39:55 by syamashi          #+#    #+#              #
#    Updated: 2021/06/15 09:16:57 by syamashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCDIR = ./srcs/
SRCS = $(shell cd $(SRCDIR) && echo *.c)
OBJDIR = ./obj/
OBJS = $(SRCS:%.c=$(OBJDIR)%.o)

CC = gcc -g -O0 -pthread
CFLAGS = -Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	@make re -s
	./$(NAME) 4 410 200 200 5
	@make fclean -s

val:
	@make re -s
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 4 410 200 200 5
	@make fclean -s

.PHONY: all fclean clean re test val