#include "lexer.h"

// read input file and print token to output file
void get_token(FILE *in, FILE *out) {
	char lexeme[LEXEME_LENGTH], token[TOKEN_LENGTH], c = ' ';
	token_name t_name;
	while ( c != EOF) {
		token[0] = 0;
		if ( isspace(c)) {
			c = (char) fgetc(in);
			continue;
		}
		if ( isalpha(c)) {
			charcpy(lexeme, c);
			int i = 0;
			for ( ; isalpha(lexeme[i]) || isdigit(lexeme[i]) || lexeme[i] == '_'; lexeme[++i] = (char) fgetc(in)) {}
			c = lexeme[i];
			lexeme[i] = 0;
			if (( t_name = is_keyword(lexeme))) {
				fputs(generate_token(token, lexeme, t_name), out);
			} else {
				fputs(generate_token(token, lexeme, IDENT), out);
			}
		} else if ( isdigit(c)) {
			charcpy(lexeme, c);
			int i = 0;
			for ( ; isdigit(lexeme[i]); lexeme[++i] = (char) fgetc(in)) {} // parse number
			c = lexeme[i];
			lexeme[i] = 0;
			fputs(generate_token(token, lexeme, NUMBER), out);
		} else {
			lexeme[0] = c;
			charcpy(lexeme + 1, (char) fgetc(in));
			if (( t_name = is_binary(lexeme))) {
				fputs(generate_token(token, lexeme, t_name), out);
				c = (char) fgetc(in);
			} else if (( t_name = is_unary(c))) {
				c = lexeme[1];
				lexeme[1] = 0;
				fputs(generate_token(token, lexeme, t_name), out);
			} else {
				c = lexeme[1];
				lexeme[1] = 0;
				fputs(generate_token(token, lexeme, NONE), out);
			}
		}
	}
}
