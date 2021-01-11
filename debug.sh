make && gcc -fsanitize=address srcs/builtin/*.o srcs/minishell/*.o srcs/parsing/*.o srcs/quote/*.o srcs/exec/*.o srcs/redirrect/*.o srcs/libft/libftprintfgnl.a && ./a.out
