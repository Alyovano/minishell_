#include "../includes/minishell.h"

void 	ft_putstr(char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
	}
}

void	ft_putstr_color(char const *s, char *str)
{
	ft_putstr(str);
	if (s)
	{
		while (*s)
			ft_putchar_fd(*s++, 1);
	}
	ft_putstr("\e[0m");
}

char	*ft_strcpy_prompt(char *dst, const char *src)
{
	char	*dest;
	size_t	i;

	dest = dst;
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *s1, const char *s2)
{
	ft_strcpy_prompt(s1 + (ft_strlen((const char*)s1)), s2);
	return (s1);
}

void		print_promt(char *cwd)
{
	if (cwd)
	{
		ft_putstr_color("[", "\033[1;34m");
		ft_putstr_color(cwd, "\033[1;34m");
		ft_putstr_color("] ", "\033[1;34m");
		ft_strcat(cwd, "/");
		ft_putstr_color(" » ", "\033[0;31m");
	}
	else
		ft_putstr_color(" » ", "\033[0;31m");
}

void		prompt(void)
{
	char *tmp;

	g_reg = 0;
	if (g_reg == 0)
	{
		tmp = getcwd(NULL, 0);
		if (tmp)
		{
			ft_putstr_color("[", "\033[1;34m");
			ft_putstr_color(tmp, "\033[1;34m");
			ft_putstr_color("] ", "\033[1;34m");
			ft_strcat(tmp, "/");
			ft_putstr_color(" » ", "\033[0;31m");
		}
		else
			ft_putstr_color(" » ", "\033[0;31m");
		free(tmp);
		//g_reg = 1;
	}
}