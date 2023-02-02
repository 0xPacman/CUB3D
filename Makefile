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
GFLAGS	=	-lmlx -framework OpenGL -framework AppKit
LIBFT	=	./libft/libft.a

SRCS	=	cube3d.c																		\
			./utils/print_errors.c					./utils/parsing/parsing_utils.c			\
			./utils/parsing/parse_colors.c			./utils/parsing/arr_utils.c				\
			./utils/parsing/initialize_map.c		./utils/parsing/parse_paths.c			\
			./utils/parsing/parse_map.c				./utils/execution/init.c				\
			./utils/execution/execution.c				\
			./utils/execution/init_screen.c				\
			./utils/execution/my_mlx_pixel_put.c 		\
			./utils/execution/key_press.c 				\
			./utils/execution/draw_screen.c 			\
			./utils/execution/dda_functions.c 			\
			./utils/execution/load_texture.c 			\
			./utils/execution/free_and_exit.c 			\
			./utils/execution/player_movement.c 		\
			./utils/execution/handle_camera.c 			\
			./utils/execution/colors.c					\
			./utils/execution/mini_map.c				\
			./utils/execution/everyframe.c				\
			./utils/execution/close_window.c			\
			./utils/execution/get_color.c				\
			./utils/execution/player_direction.c		\
			./utils/execution/which_texture_to_draw.c 	\

OBJS	=	$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@printf "\033[1;36m Compiling \033[0m LIBFT \033[1;36m√\033[0m\n"
	@$(MAKE) -s bonus -C ./libft
	@$(CC) $(LIBFT) $(GFLAGS) $^ -o $@
	@printf "\n\033[1;36m ───────────── Done ──────────── \033[0m\n\n"

%.o: %.c cube3d.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;36m Compiling \033[0m $< \033[1;36m√\033[0m\n"

all: $(NAME)

clean:
	@$(MAKE) -s clean -C ./libft
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) -s fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all