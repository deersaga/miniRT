#ifndef TOKENIZE_H
# define TOKENIZE_H
# include "minirt.h"

typedef struct s_token		t_token;

enum e_token_type {
	TK_NUM,
	TK_ID,
	TK_VEC,
};
typedef enum e_token_type	t_token_type;

struct s_token {
	t_token_type	type;
	t_element_type	id;
	FLOAT			num1;
	FLOAT			num2;
	FLOAT			num3;
	t_token			*next;
};

t_token	*tokenize(const char *buf);
#endif
