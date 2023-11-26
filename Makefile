CXX=g++
CFLAGS=-Wall -ansi -std=c++11
all : pokimacProj

pokimacProj: carte.o dresseur.o jeu.o main.o menu.o pokimac.o utils.o
	$(CXX) $(CFLAGS) $^ -o pokimacProj

carte.o: carte.cpp carte.h dresseur.h jeu.h consoleUtils.hpp utils.h menu.h
	$(CXX) -o carte.o -c carte.cpp $(CFLAGS) -lm

dresseur.o: dresseur.cpp dresseur.h pokimac.h consoleUtils.hpp utils.h jeu.h
	$(CXX) -o dresseur.o -c dresseur.cpp $(CFLAGS) -lm

jeu.o: jeu.cpp jeu.h dresseur.h pokimac.h consoleUtils.hpp utils.h carte.h
	$(CXX) -o jeu.o -c jeu.cpp $(CFLAGS) -lm

main.o: main.cpp dresseur.h carte.h menu.h pokimac.h consoleUtils.hpp utils.h jeu.h
	$(CXX) -o main.o -c main.cpp $(CFLAGS) -lm

menu.o: menu.cpp menu.h pokimac.h consoleUtils.hpp utils.h jeu.h
	$(CXX) -o menu.o -c menu.cpp $(CFLAGS) -lm

pokimac.o: pokimac.cpp pokimac.h dresseur.h utils.h
	$(CXX) -o pokimac.o -c pokimac.cpp $(CFLAGS)

utils.o: utils.cpp utils.h
	$(CXX) -o utils.o -c utils.cpp $(CFLAGS)


clean:
ifeq ($(OS),Windows_NT)
	del -f *.o
else
	rm -f *.o
endif

