SRC_DIR     	=	src
BUILD_DIR   	=	build
INCLUDE_DIRS	=	includes

SRC          	=	$(shell find $(SRC_DIR) -name "*.c")
INCLUDE_SRC		=	$(shell find $(INCLUDE_DIRS) -type d)

CC           	= 	epiclang
OBJ          	= 	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

INCLUDE      	= 	$(INCLUDE_SRC:%=-I%)
CFLAGS       	= 	-Wall -Wextra $(INCLUDE)

NAME         	= 	panoramix

COLOR_RED		=	\e[1;34m
COLOR_GREEN		=	\e[1;32m
COLOR_RESET		=	\e[0m

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_RED)Building $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB_OBJ)
	@echo "$(COLOR_RED)Linking $(NAME)$(COLOR_RESET)"
	@$(CC) -o $(NAME) $(OBJ) $(LIB_OBJ) $(CFLAGS)
	@echo "$(COLOR_GREEN)Project built successfully!$(COLOR_RESET)"

clean:
	@$(RM) wolf3D debug tests_wolf3D
	@echo "$(COLOR_GREEN)Object files cleaned!$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(BUILD_DIR)
	@echo "$(COLOR_GREEN)Project cleaned!$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re