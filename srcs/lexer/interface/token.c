#include "../lexer_internal.h"

// t_token	*token_new(t_token_type type, t_qstate state, char *str)
// {
// 	t_token	*new;

// 	new = (t_token *)x_calloc(1, sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->type = type;
// 	new->state = state;
// 	new->str = str;
// 	return (new);
// }

t_token	*token_new(t_lexer *l)
{
	t_token	*tok;

	// バッファが空で、かつエラーも起きていないならトークンを返さない
	//（例：連続する空白を飛ばした直後など）
	if (l->buf_idx == 0 && !l->is_err)
		return (NULL);

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	
	tok->str = ft_strdup(l->buffer);
	tok->type = l->current_type; // アクション関数がセットした型
	
	return (tok);
}

void	token_free(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	if (token->str)
	{
		free(token->str);
		token->str = NULL;
	}
	free(token);
}

bool	token_append(t_list **list, t_token *t)
{
	t_list	*node;

	if (!t)
		return (false);
	node = x_lstnew(t);
	if (!node)
		return (token_free(t), false);
	ft_lstadd_back(list, node);
	return (true);
}
