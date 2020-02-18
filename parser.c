#include <stdio.h>

typedef struct {
	char *str;
	int start;
	int length;
} slice_t;

typedef enum {
	spaceship, implies, arrow, lparen, rparen, mult, plus, varb, particular, error
} symbol_e;

typedef struct {
	symbol_e symb;
	slice_t *data;
} token_t;

token_t *get(slice_t *slice, symbol_e symb_e) {
	char *match;
	
	switch (symb_e) {
		case varb:
		case particular:
		int i = 0;
		for (; (i < slice->length) && alphanum(slice->str, i+(slice->start)); i++);
		slice_t *symb = malloc(sizeof(slize_t));
		symb->str = slice->str; 
		return token_t{symb, }
		case spaceship: match = "<=>"; 
		case implies: match = "=>";
		case arrow: match = "->";
		case lparen: match = "(";
		case rparen: match = ")";
		case mult: match = "*";
		case plus: match = "+";
	}
}

token_t *next(slice_t *slice) {
	switch ((slice->str)[start]) {
		case '<': return get(slice, spaceship); 
		case '-': return get(slice, implies);
		case '=': return get(slice, arrow);
		case '(': return get(slice, lparen);
		case ')': return get(slice, rparen);
		case '*': return get(slice, mult);
		case '+': return get(slice, plus);
		default:
		if ((((slice->str)[start])) > 'A' && ((slice->str)[start]) < 'Z')
			return get(slice, particular);
		if ((((slice->str)[start])) > 'a' && ((slice->str)[start]) < 'z')
			return get(slice, varb);
		return get(slice, error);
	}
}

int main(int argc, char *argv[])
{
	char *examples[] = {
		"(a -> b) -> Int",
		"(c -> d) -> Int",
		"(Stream f) -> Int",
		"(Eq a) => (Stream a) -> a",
		"(JSON -> [a]) -> [a]"
	};
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			printf("%s <=> %s\n", examples[i], examples[j]);
}