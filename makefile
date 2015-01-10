
all: human.o point.o beast.o nature.o main.o log.o random.o
	g++ random.o beast.o nature.o point.o main.o human.o log.o -Wall -g -o run -lstdc++ -lm
human.o: human.cc human.h point.h global.h
	g++ -c human.cc -lstdc++ -lm
main.o: main.cc
	g++ -c main.cc -lstdc++ -lm
point.o: point.cc point.h
	g++ -c point.cc -lstdc++ -lm
beast.o: beast.cc beast.h point.h
	g++ -c beast.cc -lstdc++ -lm
nature.o: nature.cc nature.h 
	g++ -c nature.cc -lstdc++ -lm
log.o: log.h log.cc
	g++ -c log.cc -lstdc++ -lm
random.o: random.h random.cc
	g++ -c random.cc -lstdc++ -lm 
clean:
	rm *.o
