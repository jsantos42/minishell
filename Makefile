CC	=				gcc
CFLAGS =			-Wall -Werror -Wextra
RM =				rm -rf

NAME =				minishell
HEADERS =			headers

SRCS_DIR = 			srcs
OBJS_DIR =			objs
LIBFT_DIR =			libs/libft

SRCS =				$(wildcard $(SRCS_DIR)/*.c)
OBJS =				$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
LIBS =				$(LIBFT_DIR)/libft.a
LINK =				readline

$(NAME):			CFLAGS:= $(CFLAGS) -D BONUS=0
bonus:				CFLAGS:= $(CFLAGS) -D BONUS=1

all:				$(NAME)

$(NAME):			compile_libraries $(OBJS)
						@$(CC) $(CFLAGS) -o $(NAME) -I $(HEADERS) -l$(LINK) $(LIBS) $(OBJS)
						@echo "$(NAME) mandatory successfully compiled!"

bonus:				compile_libraries $(OBJS)
						@$(CC) $(CFLAGS) -o $(NAME) -I $(HEADERS) -l$(LINK) $(LIBS) $(OBJS)
						@echo "$(NAME) bonus successfully compiled!"

compile_libraries:
						@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o:	%.c
						@mkdir -p $(dir $@)
						@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
						@make clean -C $(LIBFT_DIR)
						@$(RM) $(OBJS_DIR)
						@echo "Successfuly cleaned all object files of $(NAME)!"

fclean:				clean
						@make fclean -C $(LIBFT_DIR)
						@$(RM) $(NAME) $(LIBS)
						@echo "Successfuly cleaned all executable files of $(NAME)!"

re:					fclean	all

rebonus:			fclean	bonus

.PHONY:				all	clean	fclean	re
