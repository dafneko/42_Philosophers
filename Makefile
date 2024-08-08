# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 01:06:15 by dkoca             #+#    #+#              #
#    Updated: 2024/08/08 23:43:02 by dkoca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRCDIR := src
_SRC := main.c init.c routine.c staff.c utils.c table_manners.c liberty.c
SRC := $(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR := obj
_OBJ := $(_SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(_OBJ))

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -pedantic -Wunreachable-code -Wshadow -pthread -I$(SRCDIR)
RM := /bin/rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJ)
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	@$(MAKE) all

.PHONY:
	all clean fclean re