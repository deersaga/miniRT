#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef struct s_token		t_token;

enum e_token_type {
	TK_NUM
};
typedef enum e_token_type	t_token_type;

struct s_token {
	t_token_type	type;
	char			*word;
	t_token			*next;
};

t_token	*tokenize(const char *buf);
#endif
