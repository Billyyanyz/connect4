default: main
CC = g++
CFLAGS = -O2
main: 
	$(CC) $(CFLAGS) sdk/main.cpp sdk/json/jsoncpp.cpp Judge.cpp Strategy.cpp Board_Condition.cpp UCT.cpp -o main