SRC_DIR     	=	src
BUILD_DIR   	=	build
BUILD_DEBUG 	=	build-debug
INCLUDE_DIRS	=	includes

SRC          	=	$(shell find $(SRC_DIR) -name "*.c")
INCLUDE_SRC		=	$(shell find $(INCLUDE_DIRS) -type d)

CC           	= 	epiclang
OBJ          	= 	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_DEBUG    	= 	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DEBUG)/%.o)

INCLUDE      	= 	$(INCLUDE_SRC:%=-I%)
CFLAGS       	= 	-Wall -Wextra $(INCLUDE)
DEBUG_FLAGS  	= 	-fsanitize=address -g3 -g $(CFLAGS)

NAME         	= 	panoramix
DEBUG_NAME   	= 	debug

COLOR_RED    = \033[1;31m
COLOR_GREEN  = \033[1;32m
COLOR_RESET  = \033[0m

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(COLOR_RED)Building $<$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DEBUG)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(COLOR_RED)Building $<$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(DEBUG_NAME): $(OBJ_DEBUG) $(LIB_OBJ)
	@printf "$(COLOR_RED)Linking $(NAME)$(COLOR_RESET)\n"
	@$(CC) -o $(DEBUG_NAME) $(OBJ_DEBUG) $(LIB_OBJ) $(DEBUG_FLAGS)
	@printf "$(COLOR_GREEN)Project built successfully!$(COLOR_RESET)\n"

$(NAME): $(OBJ) $(LIB_OBJ)
	@printf "$(COLOR_RED)Linking $(NAME)$(COLOR_RESET)\n"
	@$(CC) -o $(NAME) $(OBJ) $(LIB_OBJ) $(CFLAGS)
	@printf "$(COLOR_GREEN)Project built successfully!$(COLOR_RESET)\n"

clean:
	@$(RM) panoramix debug
	@printf "$(COLOR_GREEN)Object files cleaned!$(COLOR_RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(BUILD_DIR)
	@$(RM) -r $(BUILD_DEBUG)
	@printf "$(COLOR_GREEN)Project cleaned!$(COLOR_RESET)\n"

re: fclean all

.PHONY: all clean fclean re