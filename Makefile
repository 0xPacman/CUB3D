# ************************************************************************************************** #
#                                                                                                    #
#                                                         :::   ::::::::   ::::::::  :::::::::::     #
#    Makefile                                          :+:+:  :+:    :+: :+:    :+: :+:     :+:      #
#                                                       +:+         +:+        +:+        +:+        #
#    By: ahjadani <ahjadani@student.1337.ma>           +#+      +#++:      +#++:        +#+          #
#                                                     +#+         +#+        +#+      +#+            #
#    Created: 2023/02/02 15:23:06 by ahjadani        #+#  #+#    #+# #+#    #+#     #+#              #
#    Updated: 2023/02/02 15:23:06 by ahjadani     ####### ########   ########      ###.ma            #
#                                                                                                    #
# ************************************************************************************************** #

NAME	=	cub3d
CC		=	cc
CFLAGS	=	-Werror -Wextra -Wall
LIBFT	=	./libft/libft.a
GFLAGS 	= 	-lmlx -framework OpenGL -framework AppKit
SRCS	=	cub3d.c \
			./srcs/execution/engine/engine.c \
			./srcs/execution/controls/controls.c \
			./srcs/parsing/print_error.c


OBJS	=	$(SRCS:.c=.o)

ifeq ($(UNAME),Linux)
	GFLAGS = -I /usr/local/include -lmlx -lXext -lX11 -lm
endif
ifeq ($(UNAME),Darwin)
	GFLAGS = -lmlx -framework OpenGL -framework AppKit
endif

$(NAME): $(OBJS)
	@printf "\033[1;36m Compiling \033[0m LIBFT \033[1;36m√\033[0m\n"
	@$(MAKE) -s bonus -C ./libft
	@$(CC) $(LIBFT) $(GFLAGS) $^ -o $@
	@printf "\n\033[1;36m ───────────── Done ──────────── \033[0m\n\n"

%.o: %.c ./include/cub3d.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;36m Compiling \033[0m $< \033[1;36m√\033[0m\n"

all: $(NAME)

clean:
	@$(MAKE) -s clean -C ./libft
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) -s fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all clean