#ifndef PARSING_H
# define PARSING_H

# include "struct.h"
# include "minishell.h"

int		simple_syntax(t_lex_lst *tokens);
t_cmd	*tkn_to_cmd(t_lex_lst *tokens);
void	free_cmds(t_cmd *cmds);

#endif
