#include "../includes/minishell.h"
#define FLAG_OK 0
#define FLAG_FAILURE 1
#define NO_FLAG 2
int			check_echo_flag(char *str)
{
	unsigned int i;

	i = 1;
	if (str == NULL)
		return (NO_FLAG);
	if (str[0] == '-')
	{
		while (str[i] == 'n')
		{
			i++;
		}
	}
	if (i == ft_strlen(str))
	{
		return (FLAG_OK);
	}
	return (FLAG_FAILURE);
}

int			ft_echo(t_env *env, t_list *lst)
{
	(void)env;
	int flag;

	flag = check_echo_flag(lst->flag);
	if (flag == FLAG_OK)
	{
		ft_printf("%s", lst->argu);
		return (0);
	}
	else if (flag == FLAG_FAILURE)
	{
		if (lst->flag)
			ft_printf("%s", lst->flag);
		ft_printf("%s\n", lst->argu);
		return (0);
	}
	else
	{
		ft_printf("%s\n", lst->argu);
		return (0);
	}
	return (1);
}
