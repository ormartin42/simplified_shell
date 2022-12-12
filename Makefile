NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror #-g #-fsanitize=address
RM			=	rm -rf
SRC_DIR		=	src
SRC 		=	$(notdir $(shell find $(SRC_DIR) -type f -name *.c))
INC_DIR		=	inc
IFLAGS		=	-I $(LIBFT_DIR)/inc -I $(INC_DIR) -I /Users/$(USER)/.brew/opt/readline/include
#IFLAGS		=	-I $(LIBFT_DIR)/inc -I $(INC_DIR) -I /usr/local/opt/readline/include
LIBFT_DIR	=	libft
OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
COMP_MACOS	=	-L $(LIBFT_DIR) -lft  -lreadline -L /Users/$(USER)/.brew/opt/readline/lib #changer de nom cette variable
#COMP_MACOS	=	-L $(LIBFT_DIR) -lft  -lreadline -L /usr/local/opt/readline/lib

vpath			%.c $(shell find $(SRC_DIR) -type d)
.SUFFIXES:		.c .o .h

_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]
_CLEAR		=	\033[2K\c

all				:	init $(NAME)
					@echo "$(_SUCCESS) Compilation done"

init			:
					@ $(shell mkdir -p $(OBJ_DIR))
					@ $(MAKE) --silent -C $(LIBFT_DIR)

$(NAME)			:	$(OBJ) $(INC)
					@ echo "$(_INFO) Initialize $(NAME)"
					@ $(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJ) $(COMP_MACOS)

$(OBJ_DIR)/%.o	:	%.c
					@ echo "\t$(_YELLOW)Compiling$(_RESET) $*.c\r\c"
					@ $(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
					@ echo "$(_CLEAR)"

clean			:	
					@ echo "$(_INFO) Deleting object files and directories"
					@ $(RM) $(OBJ_DIR)
					@ $(MAKE) clean --silent -C $(LIBFT_DIR)
					@ echo "$(_SUCCESS) Working directory clean"

fclean			:	clean
					@ $(MAKE) fclean --silent -C $(LIBFT_DIR)
					@ $(RM) $(NAME)

re				:	fclean all

norminette		:
					@ ~/.norminette/norminette.rb $(SRC_DIR)
					@ ~/.norminette/norminette.rb $(INC_DIR)

.PHONY:			all clean fclean re norminette

