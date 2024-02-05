#include <stdio.h>
#include "lexer/lexer.c"
#include "parser/parser.c"
#include "semanlyzr/semanlyzer.c"

//	TODO: make an error-recovery parser

#define INPUT_FILE_PATH "C:/Users/admin/CLionProjects/comp/input/input2.txt"
#define LEXER_FILE_PATH "C:/Users/admin/CLionProjects/comp/output/l_output2.txt"
#define PARSER_FILE_PATH "C:/Users/admin/CLionProjects/comp/output/p_output2.txt"

int main( void ) {
	FILE *f_in, *f_lexer, *f_parser;
	if ((f_in = fopen( INPUT_FILE_PATH, "r" )) == NULL) { perror( "input file" ); }
	else if ((f_lexer = fopen( LEXER_FILE_PATH, "w+" )) == NULL) { perror( "lexer file" ); }
	else if ((f_parser = fopen( PARSER_FILE_PATH, "w" )) == NULL) { perror( "parser file" ); }
	else {
		LexicalAnalysis( f_in, f_lexer );
		NodeAST *root = NULL;
		SyntaxAnalysis( f_lexer, f_parser, &root );

		FreeSyntaxTree( root );
		fclose( f_in );
		fclose( f_lexer );
		fclose( f_parser );
		return 0;
	}
	return 1;
}
