#include "StateMachine.h"
#include <cctype>

StateMachineClass::StateMachineClass()
	: mCurrentState(START_STATE) {
	// First, initialize all the mLegalMoves to CANTMOVE_STATE
	// Then, reset the mLegalMoves that are legitimate 
	for(int i=0; i<LAST_STATE; i++) {
		for(int j=0; j<LAST_CHAR; j++) {
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}
	
	for (int i = 0; i < LAST_CHAR; i++) {
		mLegalMoves[COMMENT_STATE][i] = COMMENT_STATE;
	}
	
	for (int i = 0; i < LAST_CHAR; i++) {
		mLegalMoves[COMMENTLINE_STATE][i] = COMMENTLINE_STATE;
	}
	
	// for (int i = 0; i < LAST_CHAR; i++) {
	// mLegalMoves[NEWLINE_STATE][i] = START_STATE;
	// }
		
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
	
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
	
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
		
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	
	mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUSEQUAL_STATE;
	
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
		
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
	mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;
	
	mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
		
	mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;
	
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	// commentline
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = COMMENTLINE_STATE;
	mLegalMoves[COMMENTLINE_STATE][NEWLINE_CHAR] = START_STATE;
	
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	
	mLegalMoves[TIMES_STATE][TIMES_CHAR] = EXPONENT_STATE;
	// block comment
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][TIMES_CHAR] = POSSIBLE_ENDCOMMENT_STATE;
	mLegalMoves[POSSIBLE_ENDCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;
	
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
	
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
	
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
	
	mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
	mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;
	
	mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	
	// First, initialize all states to correspond to the BAD token type.
	// Then, reset the end states to correspond to the correct token types.
	for(int i=0; i<LAST_STATE; i++) {
		mCorrespondingTokenType[i]=BAD_TOKEN;
	}
	
	mCorrespondingTokenType[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenType[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenType[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenType[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenType[EQUAL_STATE] = EQUAL_TOKEN;
	
	mCorrespondingTokenType[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenType[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenType[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenType[MINUS_STATE] = MINUS_TOKEN;
	
	mCorrespondingTokenType[PLUSEQUAL_STATE] = PLUSEQUAL_TOKEN;
	
	mCorrespondingTokenType[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenType[DIVIDE_STATE] = DIVIDE_TOKEN;
	
	mCorrespondingTokenType[EXPONENT_STATE] = EXPONENT_TOKEN;
	
	mCorrespondingTokenType[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenType[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenType[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenType[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenType[RCURLY_STATE] = RCURLY_TOKEN;
	
	mCorrespondingTokenType[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenType[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenType[BAD_STATE] = BAD_TOKEN;
	mCorrespondingTokenType[ENDFILE_STATE] = ENDFILE_TOKEN;
	
	// mCorrespondingTokenType[NEWLINE_STATE] = NEWLINE_TOKEN;
	
	mCorrespondingTokenType[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
	
	mCorrespondingTokenType[OR_STATE] = OR_TOKEN;
	mCorrespondingTokenType[AND_STATE] = AND_TOKEN;
	
}

MachineState StateMachineClass::UpdateState (char currentCharacter, TokenType & correspondingTokenType) {
	// convert the input character into an input character type
	CharacterType charType = BAD_CHAR;

	if (isdigit(currentCharacter))
		charType = DIGIT_CHAR;
	if (isalpha(currentCharacter))
		charType = LETTER_CHAR;
	// if (isspace(currentCharacter))
	if (currentCharacter==' ' || currentCharacter=='\t')
		charType = WHITESPACE_CHAR;
	if (currentCharacter=='+')
		charType = PLUS_CHAR;
	if (currentCharacter=='-')
		charType = MINUS_CHAR;
	if (currentCharacter=='<')
		charType = LESS_CHAR;
	if (currentCharacter=='>')
		charType = GREATER_CHAR;
	if (currentCharacter=='=')
		charType = EQUAL_CHAR;
	if (currentCharacter=='*')
		charType = TIMES_CHAR;
	if (currentCharacter=='/')
		charType = DIVIDE_CHAR;
	if (currentCharacter==';')
		charType = SEMICOLON_CHAR;
	if (currentCharacter=='(')
		charType = LPAREN_CHAR;
	if (currentCharacter==')')
		charType = RPAREN_CHAR;
	if (currentCharacter=='{')
		charType = LCURLY_CHAR;
	if (currentCharacter=='}')
		charType = RCURLY_CHAR;
	if (currentCharacter=='!')
		charType = NOT_CHAR;
	if (currentCharacter=='&')
		charType = AND_CHAR;
	if (currentCharacter=='|')
		charType = OR_CHAR;
	if (currentCharacter=='\r' || currentCharacter=='\n')
		charType = NEWLINE_CHAR;
	if (currentCharacter==EOF)
		charType = ENDFILE_CHAR;
	
	if (charType == BAD_CHAR) {
		std::cerr << "Char type error on character: " << currentCharacter << std::endl;
		exit(1);
	}
	
	correspondingTokenType = mCorrespondingTokenType[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}