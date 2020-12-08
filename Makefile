# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 20:18:10 by mspyke            #+#    #+#              #
#    Updated: 2020/12/05 18:40:09 by mspyke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

I = -I./includes/

RM = rm -f

NAME = libftprintf.a

HEADER = libft.h ft_printf.h

LIB_HEADER = $(addprefix includes/, $(HEADER))

SRC_DIR = src/
LIB_DIR = libft/

SRC_FILES = ft_printf.c ft_printf_signed.c ft_printf_spec.c \
			ft_printf_text.c ft_printf_unsigned.c ft_printf_type_parser.c

LIB_FILES = ft_atoi.c ft_isdigit.c ft_islower.c ft_putchar.c \
			  ft_putnbr.c ft_putstr.c ft_putunbr.c ft_str_to_upper.c \
			  ft_strdup.c ft_strncpy.c ft_strrev.c ft_substr.c \
			  ft_toupper.c ft_calloc.c ft_strlen.c

OBJ = $(SRC:.c=.o) $(LIBFT:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
LIBFT = $(addprefix $(LIB_DIR), $(LIB_FILES))

all: $(NAME)

$(NAME): $(OBJ) 
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c $(LIB_HEADER)
	gcc $(FLAGS) -c $< -o $@ $(I)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
