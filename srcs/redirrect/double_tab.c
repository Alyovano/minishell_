#include "../includes/minishell.h"

char	**add_str_to_tab(char **tab, char *str)
{
	char **ret;
	int i;

	i = 0;
	if (double_tab_size(tab) == 0)
		ret = malloc(sizeof(char *) * (double_tab_size(tab) + 2));
	else
		ret = malloc(sizeof(char *) * (double_tab_size(tab) + 1));
	if (!ret)
		malloc_error();
	while (tab[i] && double_tab_size(tab) > 0)
	{
		ret[i] = ft_strdup(tab[i]);
		i++;
	}
	ret[i] = ft_strdup(str);
	ret[++i] = NULL;
	return (ret);
}

void	print_double_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		ft_printf("Double tab content: |%s| id: %d\n", tab[i], i);
}