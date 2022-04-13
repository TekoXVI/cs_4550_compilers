all: main

COMMON_OBJECTS := Scanner.o StateMachine.o Token.o Symbol.o Node.o Parser.o 

COMMON_HEADERS := Debug.h

main: main.o $(COMMON_OBJECTS)
	g++ -o $@ $^
	
main.o: main.cpp $(COMMON_HEADERS)
	g++ -c $<
	
Scanner.o: Scanner.cpp Scanner.h Token.h StateMachine.o $(COMMON_HEADERS)
	g++ -c $<
	
StateMachine.o: StateMachine.cpp StateMachine.h Token.h $(COMMON_HEADERS)
	g++ -c $<
	
Token.o: Token.cpp Token.h $(COMMON_HEADERS)
	g++ -c $<

Symbol.o: Symbol.cpp Symbol.h
	g++ -c $<
	
Node.o: Node.cpp Node.h Symbol.h
	g++ -c $<
	
Parser.o: Parser.cpp Parser.h Scanner.h Token.h Symbol.h Node.h 
	g++ -c $<

clean: 
	-rm *.o $(COMMON_OBJECTS)
	
# Scanner:
	# Statemachine
	# 
# StateMachine:
	# Token
	# 
# Token:
	# none
	# 
# Symbol:
	# none
	# 
# Node:
	# Symbol
	# 
# Parser:
	# Scanner, Token, Symbol, Node