# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wangping <wangping@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/11 17:26:22 by wxuerui           #+#    #+#              #
#    Updated: 2022/09/19 11:38:10 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

NAME	= fdf
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra $(HEADER) #-fsanitize=address -g3
LIBFT_DIR	= Libft/
MLX_DIR	= mlx/
SRCS_DIR	= srcs/
OBJS_DIR	= objs/
INCLUDE_DIR	= includes/
LIBFTFLAGS	= -L$(LIBFT_DIR) -lft
MLXFLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework Appkit
MATHFLAGS	= -lm
FDFFLAGS	= $(MLXFLAGS) $(MATHFLAGS)
HEADER	= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)$(SRCS_DIR) -I$(MLX_DIR)

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = \033[0m

#sources

SRC_FILES	= 

SRCS	= $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

#######

all:
		@mkdir -p $(OBJS_DIR)
		@make create_libft
		@make create_mlx
		@make $(NAME)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@$(CC) $(CFLAGS) -c $^ -o $@
				@echo ".\c"

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(LIBFTFLAGS) $(FDFFLAGS) $(OBJS) -o $(NAME)
			@echo "\n$(GREEN)$(NAME) was created$(RESET)"

create_libft:
				@make -C $(LIBFT_DIR)

create_mlx:
				@make -C $(MLX_DIR)

bonus:	all

clean:
		@rm -rf $(OBJS_DIR)
		@make -C $(LIBFT_DIR) fclean
		@make -C $(MLX_DIR) fclean
		@echo "$(BLUE)$(NAME): $(YELLOW)object files are cleaned$(RESET)"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(BLUE)$(NAME): $(MAGENTA)$(NAME) was deleted$(RESET)"

re:	fclean all

f:
		@rm -f $(NAME)
		@echo "$(BLUE)$(NAME): $(MAGENTA)$(NAME) was deleted$(RESET)"

.PHONY:	all $(NAME) fclean ffclean clean re
