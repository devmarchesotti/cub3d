NAME = cub3D

LIBFT_PATH = ./libs/libft/
LIBFT = $(LIBFT_PATH)libft.a
LIBMLX	:= ./libs/MLX42
LIBS = -L$(LIBFT_PATH) -lft $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_DIR = ./src/

MAIN_DIR = $(SRC_DIR)main/
MAIN_SRC =	main.c \
			input_handler.c \
			input_handler_2.c \
			setup.c
MAIN = $(addprefix $(MAIN_DIR), $(MAIN_SRC))

PARSER_DIR = $(SRC_DIR)parser/
PARSER_SRC = 	parser.c \
				file_reader.c \
				utils_1.c \
				texture_2.c \
				texture.c \
				color.c \
				map_utils_1.c \
				map_utils_2.c \
				validate_input.c \
				validate_input_2.c \
				map.c
PARSER = $(addprefix $(PARSER_DIR), $(PARSER_SRC))


UTILS_DIR = $(SRC_DIR)utils/
UTILS_SRC = free_dom.c \
			free_dom_2.c \
			tool-box.c
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_SRC))

RAYCASTING_DIR = $(SRC_DIR)raycasting/
RAYCASTING_SRC = raycasting.c \
					dda.c \
					drawing.c \
					ray_processor.c \
					ray_calculation.c
RAYCASTING = $(addprefix $(RAYCASTING_DIR), $(RAYCASTING_SRC))


SRC = $(MAIN) $(PARSER) $(UTILS) $(RAYCASTING)


OBJ_DIR = ./obj/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR = ./includes/

CC = cc
FLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LIBFT_PATH)

RM = rm -f

INCLUDE = cub3D.h


all: libmlx $(LIBFT) $(NAME)

$(NAME): $(OBJ) Makefile
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@echo "Compilation $(NAME) done"

$(LIBFT): 
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory > /dev/null 2>&1

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

clean: 
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory > /dev/null 2>&1
	@$(RM) -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@echo "Clean done"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory > /dev/null 2>&1
	@$(RM) $(NAME)
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean