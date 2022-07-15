/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:47:17 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/07/15 20:42:15 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sync_arg(t_cmd_lst *cmd_t, char *old_input, char *new_input)
{
	int	idx;

	idx = 0;
	while (idx < cmd_t->arg_c)
	{
		if (ft_strncmp(cmd_t->arg_v[idx], old_input, -1) == 0)
		{
			free(cmd_t->arg_v[idx]);
			cmd_t->arg_v[idx] = new_input;
			break ;
		}
		idx++;
	}
}

int	parse_redirections(t_cmd_lst *cmd_t)
{
	int		i;
	int		j;
	int		k;
	int		idx;
	int 	len;
	char	c;
	char	**path_type;
	char	*tmp;

	path_type = &cmd_t->output_path;
	c = '>';
	j = 0;
	while (j < 2)
	{
		if (j == 1)
		{
			path_type = &cmd_t->input_path;
			c = '<';
		}
		i = 0;
		while (i < cmd_t->arg_c)
		{
			idx = 0;
			while (cmd_t->arg_v[i][idx])
			{

				
				if (cmd_t->arg_v[i][idx] == c)
				{
					if (cmd_t->arg_v[i][idx + 1] == c)
					{
						cmd_t->output_type = 'A';
						idx++;
					}
					if (cmd_t->arg_v[i][idx + 1])
					{
						// PARSE echo bon>jour
						// idx:          |
						// idx+1:         |

						len = idx + 1;
						while (cmd_t->arg_v[i][len] && cmd_t->arg_v[i][len] != '>' && cmd_t->arg_v[i][len] != '<')
							len++;

						*path_type = malloc(sizeof(char) * len - idx);
						k = 0;
						while (k < len - (idx + 1))
						{
							(*path_type)[k] = cmd_t->arg_v[i][idx + 1 + k];
							k++;
						}
						(*path_type)[k] = '\0';

						if (cmd_t->output_type == 'A')
							str_replace_sub(cmd_t->arg_v[i], "", idx - 1, len);
						else
						{
							str_replace_sub(cmd_t->arg_v[i], "", idx, len);
							cmd_t->output_type = 'R';
						}
						i = -1;
						break ;

					}
					else if (cmd_t->arg_v[i + 1])
					{

						// PARSE echo bon> jour

						len = 0;
						while (cmd_t->arg_v[i + 1][len] && cmd_t->arg_v[i + 1][len] != '>' && cmd_t->arg_v[i + 1][len] != '<')
							len++;
						*path_type = malloc(sizeof(char) * (len + 1));
						k = 0;
						while (k < len)
						{
							(*path_type)[k] = cmd_t->arg_v[i + 1][k];
							k++;
						}
						(*path_type)[k] = '\0';

						tmp = malloc(sizeof(char) * 2);
						if (!tmp)
							return (-1);
						tmp[0] = c;
						tmp[1] = '\0';
						k = 0;
						printf("String avant: %s\n", cmd_t->arg_v[i]);
						while (k < 2)
						{
							if (replace_sub_in_str(cmd_t, &cmd_t->arg_v[i], tmp, "") == -1)
								return (-1);
							k++;
						}
						free(tmp);
						printf("String après: %s\n", cmd_t->arg_v[i]);
						
						printf("%d %s %zu\n", i, cmd_t->arg_v[i], ft_strlen(cmd_t->arg_v[i]));
						
						if (ft_strlen(cmd_t->arg_v[i]) == 0)
							ft_pop(cmd_t->arg_v, i, cmd_t->arg_c--);

						for (int a = 0; cmd_t->arg_v[a]; a++)
							printf("Arg %d: |%s|\n", a, cmd_t->arg_v[a]);

						if (cmd_t->output_type == 'A')
						{
							// replace_sub_in_str(cmd_t, &cmd_t->arg_v[i], );
							str_replace_sub(cmd_t->arg_v[i + 1], "", 0, len);
							str_replace_sub(cmd_t->parsing_v[i + 1], "", 0, len);
						}
						else
						{
							str_replace_sub(cmd_t->arg_v[i + 1], "", 0, len);
							str_replace_sub(cmd_t->parsing_v[i + 1], "", 0, len);
							cmd_t->output_type = 'R';
						}
						i = -1;
						break ;

					}
				}

				idx++;
			}
			i++;
			idx = 0;
			while (idx < cmd_t->arg_c)
			{
				if (ft_strlen(cmd_t->arg_v[idx]) == 0)
				{
					ft_pop(cmd_t->arg_v, idx, cmd_t->arg_c--);
					idx = 0;
				}
				else
					idx++;
			}
		}
		j++;
	}
	idx = 0;
	while (idx < cmd
	return (0);
}

/*
	By default, all chars have meaning
	D = Escaped by double quotes (no meaning)
	S = Escaped by simple quotes (no meaning)
	M = Meaning
	E = This quote has been managed, remove it from the string
*/
int	parse_input_quotes(char *input, char *parse)
{
	int		i;
	int		idx;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' && parse[i] != 'S')
		{
			parse[i] = 'E';
			idx = i + 1;
			while (input[idx] != '\"')
			{
				if (input[idx] != '$')
					parse[idx] = 'D';
				idx++;
			}
			parse[idx] = 'E';
			i = idx;
		}
		else if (input[i] == '\'' && parse[i] != 'D')
		{
			parse[i] = 'E';
			idx = i + 1;
			while (input[idx] != '\'')
				parse[idx++] = 'S';
			parse[idx] = 'E';
			i = idx;
		}
		i++;
	}
	return (0);
}

int	parse_quotes(t_cmd_lst *cmd_t, t_list *env)
{
	int		i;
	int		idx;
	size_t	len;
	t_list	*val;
	char	*sub;
	char 	*subparsing;

	cmd_t->parsing_v = malloc(sizeof(char *) * (cmd_t->input_c + 1));

	i = 0;
	while (i < cmd_t->input_c)
	{
		cmd_t->parsing_v[i] = malloc(sizeof(char) * (ft_strlen(cmd_t->input_v[i]) + 1));
		len = 0;
		while (len < ft_strlen(cmd_t->input_v[i]))
			cmd_t->parsing_v[i][len++] = 'M';
		cmd_t->parsing_v[i][len] = '\0';
		i++;
	}

	i = 0;
	while (i < cmd_t->input_c)
	{
		parse_input_quotes(cmd_t->input_v[i], cmd_t->parsing_v[i]);
		i++;
	}

	i = 0;
	while (i < cmd_t->input_c)
	{
		idx = 0;
		while (cmd_t->input_v[i][idx])
		{
			if (cmd_t->parsing_v[i][idx] == 'E')
			{
				printf("1: %s (%d)\n", cmd_t->input_v[i], idx);
				if (remove_char_from_str(cmd_t, &cmd_t->input_v[i], idx) == -1)
					return (-1);
				printf("2: %s\n", cmd_t->input_v[i]);
				if (remove_char_from_str(NULL, &cmd_t->parsing_v[i], idx) == -1)
					return (-1);
			}
			else
				idx++;
		}
		i++;
	}

	sub = NULL;
	i = 0;
	while (i < cmd_t->input_c)
	{
		idx = 0;
		while (cmd_t->input_v[i] && cmd_t->input_v[i][idx])
		{
			if (cmd_t->input_v[i][idx] == '$' && cmd_t->parsing_v[i][idx] == 'M')
			{
				len = 0;
				idx++;
				while (cmd_t->parsing_v[i][idx] && \
					(cmd_t->parsing_v[i][idx] == 'D' || cmd_t->parsing_v[i][idx] == 'M') && \
					cmd_t->input_v[i][idx] != '$' && cmd_t->input_v[i][idx] != '\'' && cmd_t->input_v[i][idx] != '\"')
				{
					len++;
					idx++;
				}
				
				sub = ft_substr(cmd_t->input_v[i], idx - len, len);
				if (!sub)
					return (-1);
				subparsing = ft_substr(cmd_t->parsing_v[i], idx - len, len);
				if (!subparsing)
					return (-1);
				printf("==> Environment variable detected: |%s|\n", sub);
				val = get_env_by_id(env, sub);
				if (val)
				{
					if (remove_char_from_str(cmd_t, &cmd_t->input_v[i], idx - len - 1) == -1)
						return (-1); // memory error
					if (replace_sub_in_str(cmd_t, &cmd_t->input_v[i], sub, val->value) == -1)
						return (-1); // memory error
					free(sub);
					sub = ft_strdup_char('D', ft_strlen(val->value));
					if (!sub)
						return (-1); // memory error
					if (replace_sub_in_str(NULL, &cmd_t->parsing_v[i], subparsing, sub) == -1)
						return (-1); // memory error
					free(sub);
					free(subparsing);
					idx += (ft_strlen(val->value) - (len + 2));
				}
				else
				{
					if (replace_sub_in_str(cmd_t, &cmd_t->input_v[i], sub, "") == -1)
						return (-1);
					free(sub);
					if (replace_sub_in_str(NULL, &cmd_t->parsing_v[i], subparsing, "") == -1)
						return (-1); // memory error
					free(subparsing);
					idx -= (len + 2);
				}
			}
			idx++;
		}
		i++;
	}

	return (0);
}

int	parse_options(t_cmd_lst *cmd_t)
{
	int	i;
	int	idx;

	cmd_t->options_v = malloc(sizeof(char *) * (cmd_t->options_c + 1));
	if (!cmd_t->options_v)
		return (-1);
	i = 1;
	idx = 0;
	while (i < cmd_t->arg_c)
	{
		if (cmd_t->arg_v[i][0] == '-')
			cmd_t->options_v[idx++] = cmd_t->arg_v[i];	
		i++;
	}
	cmd_t->options_v[idx] = NULL;
	return (0);
}

int	parse_input(t_cmd_lst *cmd_t)
{
	int	i;
	int	idx;

	cmd_t->input_v = malloc(sizeof(char *) * (cmd_t->input_c + 1));
	if (!cmd_t->input_v)
		return (-1);
	i = 1;
	idx = 0;
	while (i < cmd_t->arg_c)
	{
		if (cmd_t->arg_v[i][0] != '-')
			cmd_t->input_v[idx++] = cmd_t->arg_v[i];	
		i++;
	}
	cmd_t->input_v[idx] = NULL;
	return (0);
}

void	parse_counts(t_cmd_lst *cmd_t)
{
	int	idx;

	idx = 1;
	cmd_t->input_c = 0;
	cmd_t->options_c = 0;
	while (idx < cmd_t->arg_c)
	{
		if (cmd_t->arg_v[idx][0] == '-')
			cmd_t->options_c++;
		else
			cmd_t->input_c++;
		idx++;
	}
}
