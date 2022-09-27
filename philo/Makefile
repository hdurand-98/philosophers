# Colors

C_GREY		=	\033[1;30m
C_RED		=	\033[1;31m
C_GREEN		=	\033[1;32m
C_YELLOW	=	\033[1;33m
C_BLUE		=	\033[1;34m
C_PURPLE	=	\033[1;35m
C_CYAN		=	\033[1;36m
C_WHITE		=	\033[1;37m
C_END		=	\033[0m


NAME	=	philo

CC	=	gcc

RM	=	rm -rf

CP	=	cp -r

CFLAGS	=	-D_REENTRANT -c -g3 -Wall -Wextra -Werror -fsanitize=thread

TFLAGS	=	-lncurses -lpthread -fsanitize=thread

SRC		+=	main.c
SRC		+=	ft_atoi.c
SRC		+=	forks.c
SRC		+=	collect_info.c
SRC		+=	philo_actions.c
SRC		+=	clocks.c
SRC		+=	ft_isdigit.c

OBJ_PATH	=	./.obj/

vpath %.c .

OBJ		=	$(patsubst %.c, $(OBJ_PATH)%.o, $(SRC))

HEADER_NAME	=	philo.h

HEADER_PATH	=	./include

HEADER		=	$(addprefix $(HEADER_PATH)/, $(HEADER_NAME))

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ)
	@$(CC) -I$(HEADER_PATH)/ -o $(NAME) $(OBJ) $(TFLAGS)
	@echo "$<		[$(C_GREEN)OK$(C_END)]"

$(OBJ): $(OBJ_PATH)%.o: %.c $(HEADER)
	@$(CC) -I$(HEADER_PATH)/ $(CFLAGS) $< -o $@

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
