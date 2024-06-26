/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:20 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 11:31:21 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_correspon(char **env, char **argv)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (argv[i])
	{
		j = 0;
		while (env[j])
		{
			if (!ft_strncmp(env[j], argv[i], ft_strlen(argv[i])))
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}

static void	copy_except(char **new_env, char **argv, t_minishell *param)
{
	int		i;
	int		j;
	int		k;
	bool	should_copy;

	i = -1;
	k = 0;
	while (param->env_variables[++i])
	{
		should_copy = true;
		j = 0;
		while (argv[++j])
		{
			if (!strncmp(param->env_variables[i], argv[j], strlen(argv[j])))
				should_copy = false;
			if (should_copy)
				new_env[k++] = strdup(param->env_variables[i]);
		}
	}
	new_env[k] = NULL;
}

static char	**renew_arr(char **argv, int len_arr, t_minishell *param)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * \
		(len_arr + 1 - count_correspon(param->env_variables, argv)));
	if (!new_env)
		return (NULL);
	copy_except(new_env, argv, param);
	ft_free_tab(param->env_variables);
	return (new_env);
}

void	ft_unset(t_execcmd *cmd, t_minishell *param)
{
	int	len_env;

	len_env = 0;
	while (param->env_variables[len_env])
		len_env++;
	if (count_correspon(param->env_variables, cmd->argv) > 0)
		param->env_variables = renew_arr(cmd->argv, len_env, param);
	g_exit_status = 0;
}
