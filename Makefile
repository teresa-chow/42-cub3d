# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 16:14:09 by tchow-so          #+#    #+#              #
#    Updated: 2025/08/06 11:01:14 by tchow-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
BONUS	= cub3D_bonus

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC				= $(addprefix $(SRC_DIR)/, main.c)
SRC_PARSER		= $(addprefix $(PARSER_DIR)/, check_config_color.c \
	check_config_map.c check_config_tex.c check_config.c check_input.c \
	get_config_map.c get_config_map2.c check_config_tex_utils.c \
	check_config_map_utils.c utils.c)
SRC_RENDERER	= $(addprefix $(RENDERER_DIR)/, calc_movement.c calc_rotation.c \
	event_log.c graphics_utils.c raycaster_calc00.c raycaster_calc01.c \
	raycaster_texture00.c raycaster_texture01.c render_frame.c render_launch.c \
	render_wall.c time_management.c)
SRC_RENDERER_BONUS	= $(addprefix $(SRC_DIR)/, main_bonus.c) $(addprefix $(RENDERER_DIR)/, \
	calc_movement.c calc_rotation.c event_log.c graphics_utils.c raycaster_calc00.c \
	raycaster_calc01.c raycaster_texture00.c raycaster_texture01.c render_wall.c \
	time_management.c) $(addprefix $(RENDERER_DIR_BONUS)/, minimap_bonus.c \
	minimap_grid_bonus.c minimap_player_bonus.c render_frame_bonus.c \
	render_launch_bonus.c)
SRC_UTILS		= $(addprefix $(UTILS_DIR)/, error_handling.c memory_management.c \
	print_error.c)

OBJS				= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
OBJS_PARSER			= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_PARSER:.c=.o)))
OBJS_RENDERER		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_RENDERER:.c=.o)))
OBJS_RENDERER_BONUS	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_RENDERER_BONUS:.c=.o)))
OBJS_UTILS			= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_UTILS:.c=.o)))

LIBFT_ARC	= $(LIBFT_DIR)/libft.a


# ============================================================================ #
# PATHS                                                                        #
# ============================================================================ #

INC_DIR				= include
SRC_DIR 			= src
PARSER_DIR			= $(SRC_DIR)/parser
RENDERER_DIR		= $(SRC_DIR)/renderer
RENDERER_DIR_BONUS	= $(SRC_DIR)/renderer_bonus
UTILS_DIR			= $(SRC_DIR)/utils

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
	$(OBJS_RENDERER) $(OBJS_UTILS)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_PARSER) $(OBJS_RENDERER) $(OBJS_UTILS) \
	$(LIBFT_ARC) $(MLX_ARC) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GRN)>> Compiled cub3D$(NC)\n\n"

bonus: $(BONUS)	## Compile cub3D bonus (minimap)

$(BONUS): $(LIBFT_ARC) $(MLX_ARC) $(BUILD_DIR) $(OBJS_PARSER) \
	$(OBJS_RENDERER_BONUS) $(OBJS_UTILS)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS_PARSER) $(OBJS_RENDERER_BONUS) \
	$(OBJS_UTILS) $(LIBFT_ARC) $(MLX_ARC) $(MLX_FLAGS) -o $(BONUS)
	@printf "$(GRN)>> Compiled cub3D with bonus feature (minimap)$(NC)\n\n"

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(RENDERER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(RENDERER_DIR_BONUS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
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
	$(RM) $(NAME) $(BONUS)
	@printf "$(GRN)>> Removed executable files$(NC)\n\n"
	$(MAKE) $(LIBFT_DIR) fclean
	@printf "$(GRN)>> Removed Libft archive$(NC)\n\n"
	$(MAKE) $(MLX_DIR) clean
	@printf "$(GRN)>> Removed MiniLibX archive$(NC)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm:	## Execute norminette
	norminette $(INC_DIR) $(LIBFT_DIR) $(SRC_DIR)


##@ MEMORY MANAGEMENT & THREADING DEBUG

vg: all	## Run valgrind (export MAP first)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(MAP)


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
