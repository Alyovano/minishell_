#include "../includes/minishell.h"

int     change_pwd(t_env *env)
{
    int j;
    char *tmp;
    char *tmp_s;

    j = 0;
    tmp = getcwd(NULL, 0);
    tmp_s = ft_strjoin("PWD=", tmp);
    while (env->tab[j])
	{
		if (catch_env_varr("PWD", env->tab[j]) == 0)
		{
			free(env->tab[j]);
			env->tab[j] = ft_strdup(tmp_s);
		}
		j++;
	}
    free(tmp);
    free(tmp_s);
    return (0);
}

int     change_old_pwd(char *oldpwd, t_env *env)
{
    int j;
    char *tmp;
    char *tmp_s;

    j = 0;
    tmp = ft_strdup(oldpwd);
    tmp_s = ft_strjoin("OLDPWD=", tmp);
    while (env->tab[j])
	{
		if (catch_env_varr("OLDPWD", env->tab[j]) == 0)
		{
			free(env->tab[j]);
			env->tab[j] = ft_strdup(tmp_s);
		}
		j++;
	}
    free(tmp);
    free(tmp_s);
    return (0);
}

int     go_home(char *tmp, char *var_name, t_env *env)
{
    char *var_content;

    var_content = check_var_in_env(var_name, env);
    chdir(var_content);
    free(var_content);
    change_old_pwd(tmp, env);
    change_pwd(env);
    return(0);
}

int     dirr_error(char *path)
{
    ft_printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", path);
    return (0);
}

int     ft_cd(t_env *env, char *path)
{
    char *tmp;

    tmp = getcwd(NULL, 0);
    if (!path[0] || !path)
    {
        go_home(tmp, "HOME", env);
        free(tmp);
        return (0);

    }
    if (chdir(path) == 0)
    {
        change_old_pwd(tmp, env);
        change_pwd(env);
    }
    else
        dirr_error(path);
    free(tmp);
    return (0);
}
