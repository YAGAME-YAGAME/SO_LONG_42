CC = cc
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code
INCLUDES = -I ./include -I ./lib/MLX42/include

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LDFLAGS = -L ./lib/MLX42/build -lmlx42 -lX11 -lXext -lm -pthread -lglfw -ldl
else ifeq ($(UNAME_S),Darwin)
	GLFW_PATH = $(shell brew --prefix glfw)
	LDFLAGS = -L ./lib/MLX42/build -L $(GLFW_PATH)/lib -lmlx42 -lglfw -framework OpenGL -framework AppKit -ldl -pthread -lm
endif

# export LIBRARY_PATH=/Users/abenajib/.brew/opt/glfw/lib
# GLFW_PATH = $(shell brew --prefix glfw)
# LDFLAGS = -L ./lib/MLX42/build -L $(GLFW_PATH)/lib -lmlx42 -lglfw -framework OpenGL -framework AppKit -ldl -pthread -lm
# LINUX_LDFLAGS = -L ./lib/MLX42/build -lmlx42 -lX11 -lXext -lm -pthread -lglfw -ldl

SRC = ./src/so_long.c \
		./src/move.c \
		./src/move_utils.c \
		./src/map_parsing.c \
		./src/map_checkers.c \
		./src/map_checkers_2.c \
		./src/map_checkers_3.c \
		./src/game_init.c \
		./ft_printf/ft_printf.c \
		./ft_printf/ft_putchar_fd_p.c \
		./ft_printf/ft_putnbr_fd_p.c \
		./ft_printf/ft_putstr_fd_p.c \
		./ft_printf/ft_puthex_fd_p.c \
		./ft_printf/ft_putunint_fd_p.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

# Color codes for terminal output
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

TARGET = so_long

all: $(TARGET)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJ) libft ft_printf
	@$(CC) $(OBJ) ./libft/libft.a ./ft_printf/libftprintf.a $(LDFLAGS) -o $(TARGET)
	@echo "$(GREEN)______________	  ___   _____________________"
	@echo "$(GREEN)|     ||     |	  |  |   |     ||     ||     |"
	@echo "$(GREEN)|  ___!|  |  |	  |  |   |  |  ||     ||   __!"
	@echo "$(GREEN)!__   ||  |  |	  |  !___|  |  ||  |  ||  !  |"
	@echo "$(GREEN)|     ||  !  |____|     7|  !  ||  |  ||  !  |"
	@echo "$(GREEN)!_____!!_____!____!_____!!_____!!__!__!!_____!"
	@echo "$(GREEN)\n==The Makefile of [SO_LONG] has been compiled!==\n$(DEF_COLOR)"
	@echo "$(YELLOW)\n=> Usage: ./so_long <map.ber>\n$(DEF_COLOR)"

clean:
	@rm -f $(OBJ)
	@make --silent -C ./libft clean
	@make --silent -C ./ft_printf clean

fclean: clean
	@rm -f $(TARGET)
	@make --silent -C ./libft fclean
	@make --silent -C ./ft_printf fclean

re: fclean all

# Build MLX42 library
clone_mlx42:
	@git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42

mlx42:
	@echo "$(YELLOW)Building MLX42 library...$(DEF_COLOR)"
	@cmake ./lib/MLX42 -B ./lib/MLX42/build
	@make -C ./lib/MLX42/build -j4

libft:
	@echo "$(CYAN) Compiling...Please wait!\n"
	@make --silent -C libft

ft_printf:
	@make --silent -C ft_printf

.PHONY: all clean fclean re mlx42 libft ft_printf
