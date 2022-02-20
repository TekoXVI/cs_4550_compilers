all: main symboltest

COMMON_OBJECTS := Scanner.o StateMachine.o Token.o

COMMON_HEADERS := Debug.h

main: main.o $(COMMON_OBJECTS)
	g++ -o $@ $^
	
main.o: main.cpp StateMachine.h Scanner.h $(COMMON_HEADERS)
	g++ -c $<
	
Scanner.o: Scanner.cpp Scanner.h StateMachine.h $(COMMON_HEADERS)
	g++ -c $<
	
StateMachine.o: StateMachine.cpp StateMachine.h Token.h $(COMMON_HEADERS)
	g++ -c $<
	
Token.o: Token.cpp Token.h $(COMMON_HEADERS)
	g++ -c $<
	
symboltest: symboltest.o Symbol.o
	g++ -o $@ $^
	
symboltest.o: symboltest.cpp Symbol.h
	g++ -c $<

Symbol.o: Symbol.cpp Symbol.h
	g++ -c $<
	

clean: 
	-rm *.o $(COMMON_OBJECTS)