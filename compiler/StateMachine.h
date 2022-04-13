#ifndef STATEMACHINE
#define STATEMACHINE

#include "Token.h"
#include "Debug.h"

enum MachineState {
	START_STATE, CANTMOVE_STATE, 
	// Relational Operators:
	LESS_STATE, LESSEQUAL_STATE, GREATER_STATE, GREATEREQUAL_STATE, EQUAL_STATE, NOTEQUAL_STATE,
	// Other Operators:
	INSERTION_STATE, ASSIGNMENT_STATE, PLUS_STATE, MINUS_STATE, TIMES_STATE, DIVIDE_STATE, 
	EXPONENT_STATE, PLUSEQUAL_STATE,
	// Other Characters:
	SEMICOLON_STATE, LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE,
	// Other STATE Types:
	IDENTIFIER_STATE, INTEGER_STATE, 
	BAD_STATE, ENDFILE_STATE,
	/*NEWLINE_STATE,*/
	COMMENT_STATE, POSSIBLE_ENDCOMMENT_STATE,
	COMMENTLINE_STATE,
	NOT_STATE,
	AND_STATE, OR_STATE,
	LAST_STATE
};

enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, BAD_CHAR, MINUS_CHAR,
	LESS_CHAR, GREATER_CHAR, EQUAL_CHAR, 
	TIMES_CHAR, DIVIDE_CHAR, SEMICOLON_CHAR, 
	LPAREN_CHAR, RPAREN_CHAR, LCURLY_CHAR, RCURLY_CHAR,
	NOT_CHAR, OR_CHAR, AND_CHAR,
	NEWLINE_CHAR,
	ENDFILE_CHAR,
	LAST_CHAR
};

class StateMachineClass {
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType & correspondingTokenType);

private:
	MachineState mCurrentState;

	// The matrix of legal moves:
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];
	// Which end-machine-states correspond to which token types.
	// (non end states correspond to the BAD_TOKEN token type)
	TokenType mCorrespondingTokenType[LAST_STATE];
};

#endif //STATEMACHINE