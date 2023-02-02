#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahjadani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 23:12:58 by ahjadani          #+#    #+#              #
#    Updated: 2021/11/13 22:12:25 by ahjadani         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC	= 	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnlen.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c

BONUS_SRC =	ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRC:.c=.o)

BONUS_OBJECTS= $(BONUS_SRC:.c=.o)

NAME = libft.a
CC = gcc
RM = rm -f
AR = ar rcs

all: $(NAME)

clean:
		$(RM) $(OBJECTS) $(BONUS_OBJECTS)

rmout:
		$(RM) a.out

%.o: %.c
		$(CC) $(CFLAGS) -c -I./ $< -o $@

$(NAME): $(OBJECTS)
		$(AR) $(NAME) $(OBJECTS)

bonus: $(OBJECTS) $(BONUS_OBJECTS)
		$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
