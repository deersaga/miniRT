#ifndef PARSE_H
#define PARSE_H

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

enum s_token_type {

};

struct s_token {
	t_token_type	type;

	t_token			*next;
}:

#endif