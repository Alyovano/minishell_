BUILTIN = $(addprefix srcs/builtin/, export.c)
MINISHELL = $(addprefix srcs/minishell/, minishell.c)
PARSING = $(addprefix srcs/parsing/, backslash.c parsing.c)
QUOTE = $(addprefix srcs/quote/, check_quote.c multilines_quote.c)

SRCS		= 	$(BUILTIN)					\
				$(MINISHELL)				\
				$(PARSING)					\
				$(QUOTE) 					\

INCL		= 	srcs/includes/

OBJS		= 	${SRCS:.c=.o}

LIBFTPRINTF	= 	srcs/libft/libftprintfgnl.a

NAME		= 	minishell

CC			= 	gcc

RM			= 	rm -f

CFLAGS 		= 	-Wall -Wextra -Werror -I ${INCL}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C srcs/libft
			${CC} -o ${NAME} ${OBJS} ${LIBFTPRINTF}

all:		${NAME}

clean:
			${RM} ${OBJS}
			make clean -C srcs/libft
fclean:		clean
			${RM} ${NAME}
			make fclean -C srcs/libft

re:			fclean all

.PHONY:		clean fclean re all bonus