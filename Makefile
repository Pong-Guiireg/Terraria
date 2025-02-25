# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Couleurs
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Dossiers
SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
OBJ_DIR = obj

# Fichiers
SRC = $(wildcard $(SRC_DIR)/*.c)
LIB = $(wildcard $(LIB_DIR)/*.c)
ALL_SRC = $(SRC) $(LIB)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC)) $(patsubst $(LIB_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB))
HDR = $(wildcard $(INC_DIR)/*.h)
NAME = Terraria
ERROR_FILE = errors.txt

.SILENT:

all: init $(NAME)

init:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "$(BLUE)[INFO]$(RESET) Linking objects..."
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) 2> $(ERROR_FILE) || (echo "$(RED)[ERROR]$(RESET) Linking failed, see $(ERROR_FILE)" && exit 1)
	@echo "$(GREEN)[OK]$(RESET) Binary $(NAME) created successfully!"
	@[ -s $(ERROR_FILE) ] || rm -f $(ERROR_FILE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@echo "$(BLUE)[INFO]$(RESET) Compiling $<..."
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@ 2> $(ERROR_FILE) || (echo "$(RED)[ERROR]$(RESET) Compilation of $< failed, see $(ERROR_FILE)" && exit 1)
	@echo "$(GREEN)[OK]$(RESET) Object $@ created successfully!"
	@[ -s $(ERROR_FILE) ] || rm -f $(ERROR_FILE)

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c $(HDR)
	@echo "$(BLUE)[INFO]$(RESET) Compiling library $<..."
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@ 2> $(ERROR_FILE) || (echo "$(RED)[ERROR]$(RESET) Compilation of $< failed, see $(ERROR_FILE)" && exit 1)
	@echo "$(GREEN)[OK]$(RESET) Library object $@ created successfully!"
	@[ -s $(ERROR_FILE) ] || rm -f $(ERROR_FILE)

clean:
	@echo "$(YELLOW)[INFO]$(RESET) Cleaning object files..."
	rm -rf $(OBJ_DIR)
	@echo "$(GREEN)[OK]$(RESET) Object files removed successfully!"

fclean: clean
	@echo "$(YELLOW)[INFO]$(RESET) Cleaning binary..."
	rm -f $(NAME)
	rm -f $(ERROR_FILE)
	@echo "$(GREEN)[OK]$(RESET) Binary $(NAME) removed successfully!"

re: fclean all

.PHONY: all init clean fclean re
