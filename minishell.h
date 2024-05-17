/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:53:34 by dabae             #+#    #+#             */
/*   Updated: 2024/05/17 11:43:22 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft/libft.h"

enum e_token
{
	EXEC,
	PIPE,
	REDIR,
	ENVIRONMENT,
};

typedef struct s_cmd
{
	enum e_token	type;
}			t_cmd;

typedef struct s_execcmd
{
	enum e_token	type;
	char			*argv[100];
	char			*end_argv[100];
}				t_execcmd;

typedef struct s_pipecmd
{
	enum e_token	type;
	t_cmd			*left;
	t_cmd			*right;
}				t_pipecmd;

typedef struct s_redircmd
{
	enum e_token	type;
	t_cmd			*cmd;
	char			*start_file;
	char			*end_file;
	int				mode;
	int				fd;
}				t_redircmd;

//constructor
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *sub_cmd, char *s_file, char *e_file, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);



// parsing
bool	peek(char **start_str, char *end_str, char *c);
int		get_token(char **start_line, char *end_line, char **start_t, char **end_t);
int		parse(char *line);

#endif