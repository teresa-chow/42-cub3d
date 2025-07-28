# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 16:14:09 by tchow-so          #+#    #+#              #
#    Updated: 2025/07/26 09:29:26 by tchow-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC				= $(addprefix $(SRC_DIR)/, main.c)
SRC_PARSER		= $(addprefix $(PARSER_DIR)/, check_config_color.c \
	check_config_map.c check_config_tex.c check_config.c check_input.c \
	error_handling.c get_config_map.c memory_management.c check_config_tex_utils.c \
	check_config_map_utils.c utils.c)
SRC_RENDERER	= $(addprefix $(RENDERER_DIR)/, calc_movement.c calc_rotation.c \
	event_log.c graphics_utils.c minimap.c minimap_grid.c minimap_player.c \
	raycaster_calc00.c raycaster_calc01.c raycaster_texture.c render_frame.c \
	render_launch.c time_management.c)

OBJS			= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
OBJS_PARSER		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_PARSER:.c=.o)))
OBJS_RENDERER	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_RENDERER:.c=.o)))

LIBFT_ARC	= $(LIBFT_DIR)/libft.a


# ============================================================================ #
# PATHS                                                                        #
# ============================================================================ #

INC_DIR			= include
SRC_DIR 		= src
PARSER_DIR		= $(SRC_DIR)/parser
RENDERER_DIR	= $(SRC_DIR)/renderer

BUILD_DIR	= .build
LIB_DIR		= lib

# Libraries
LIBFT_DIR	= $(LIB_DIR)/libft


# ============================================================================ #
# OS-SPECIFIC VARIABLES                                                        #
# ============================================================================ #

ifeq ($(shell uname), Darwin)
	MLX_DIR		= $(LIB_DIR)/minilibx_macos
	MLX_ARC	= $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
	MLX_DIR		= $(LIB_DIR)/minilibx-linux
	MLX_ARC		= $(MLX_DIR)/libmlx_Linux.a
	MLX_FLAGS = -L$(MLX_DIR) -lXext -lX11 -lm -lz -no-pie
endif


# ============================================================================ #
# COMPILER, FLAGS & COMMANDS                                                   #
# ============================================================================ #

CC		= cc
CFLAGS	=  -Wall -Wextra -Werror
CFLAGS	+= -g

MAKE	= make -C

RM		= rm -rf
AR		= ar rcs
MKDIR	= mkdir -p


# ============================================================================ #
# RULES                                                                        #
# ============================================================================ #

##@ COMPILATION RULES

all: $(NAME)	## Compile cub3D

$(NAME): $(LIBFT_ARC) $(MLX_ARC) $(BUILD_DIR) $(OBJS) $(OBJS_PARSER) \
	$(OBJS_RENDERER)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_PARSER) $(OBJS_RENDERER) \
	$(LIBFT_ARC) $(MLX_ARC) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GRN)>> Compiled cub3D$(NC)\n\n"


$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(RENDERER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Library directories
$(MLX_DIR):
	@if [ "$(shell uname)" = "Darwin" ]; then \
	    git clone https://github.com/World42/minilibx_macos.git lib/minilibx_macos; \
	else \
	    git clone https://github.com/42Paris/minilibx-linux.git lib/minilibx-linux; \
	fi
	@printf "$(GRN)>> Cloned MiniLibX$(NC)\n\n"

# Library archives
$(LIBFT_ARC): $(LIBFT_DIR)
	$(MAKE) $(LIBFT_DIR)
	@printf "$(GRN)>> Created Libft archive$(NC)\n\n"

$(MLX_ARC): $(MLX_DIR)
	$(MAKE) $(MLX_DIR)
	@printf "$(GRN)>> Created MiniLibX archive$(NC)\n\n"


##@ CLEAN-UP RULES

clean:	## Remove object files
	$(RM) $(BUILD_DIR)
	$(MAKE) $(LIBFT_DIR) clean
	$(MAKE) $(MLX_DIR) clean
	@printf "$(GRN)>> Removed object files$(NC)\n\n"

fclean: clean	## Remove executable files
	$(RM) $(NAME)
	@printf "$(GRN)>> Removed executable files$(NC)\n\n"
	$(MAKE) $(LIBFT_DIR) fclean
	@printf "$(GRN)>> Removed Libft archive$(NC)\n\n"
	$(MAKE) $(MLX_DIR) clean
	@printf "$(GRN)>> Removed MiniLibX archive$(NC)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm: all	## Execute norminette
	norminette $(INC_DIR) $(LIBFT_DIR) $(SRC_DIR)


##@ MEMORY MANAGEMENT & THREADING DEBUG

vg: all	## Run valgrind
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) .cub


##@ TOOL INSTALLATION

install: ## Install norminette and valgrind
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette
	sudo apt install valgrind -y


##@ HELP

help:	## Display this help info
	@awk 'BEGIN { \
		FS = ":.*##"; \
		printf "\n$(WHI_B)USAGE$(NC)\n\t$(YEL)make$(NC)$(CYA)\t \
		<target>$(NC)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
		printf "\t$(CYA_B)%-15s$(NC) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(WHI_B)%s$(NC)\n", \
		substr($$0, 5) } ' Makefile
	@printf "\n"

.PHONY: all clean fclean re norm vg install help


# ============================================================================ #
# UTILS: SHELL FORMATTING                                                      #
# ============================================================================ #

# Reset to default
NC = \033[0m

# Regular text colors
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYA = \033[0;36m
WHI = \033[0;37m

# Bold text colors
RED_B = \033[1;31m
GRN_B = \033[1;32m
YEL_B = \033[1;33m
BLU_B = \033[1;34m
MAG_B = \033[1;35m
CYA_B = \033[1;36m
WHI_B = \033[1;37m
