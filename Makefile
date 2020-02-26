CC=c++
CFLAGS=-lsfml-window -lsfml-system -lsfml-graphics -c -std=c++17
COMPILE_FLAGS=-lsfml-window -lsfml-system -lsfml-graphics -std=c++17
CODE_DIR=Data/Code/

all: planes1

planes1: main.o backgrounds.o balloon.o bullet.o cloud.o explosion.o paratroopers.o people.o plane.o load.o updateNPC.o singlePlayerGame.o
	$(CC) main.o backgrounds.o balloon.o bullet.o cloud.o explosion.o paratroopers.o people.o plane.o load.o updateNPC.o singlePlayerGame.o -o planes $(COMPILE_FLAGS);

main.o: main.cpp
	$(CC) main.cpp $(CFLAGS)

backgrounds.o: $(CODE_DIR)backgrounds.cpp
	$(CC) $(CODE_DIR)backgrounds.cpp $(CFLAGS)

balloon.o: $(CODE_DIR)balloon.cpp
	$(CC) $(CODE_DIR)balloon.cpp $(CFLAGS)

bullet.o: $(CODE_DIR)bullet.cpp
	$(CC) $(CODE_DIR)bullet.cpp $(CFLAGS)

cloud.o: $(CODE_DIR)cloud.cpp
	$(CC) $(CODE_DIR)cloud.cpp $(CFLAGS)

explosion.o: $(CODE_DIR)explosion.cpp
	$(CC) $(CODE_DIR)explosion.cpp $(CFLAGS)

paratroopers.o: $(CODE_DIR)paratroopers.cpp
	$(CC) $(CODE_DIR)paratroopers.cpp $(CFLAGS)

people.o: $(CODE_DIR)people.cpp
	$(CC) $(CODE_DIR)people.cpp $(CFLAGS)

plane.o: $(CODE_DIR)plane.cpp
	$(CC) $(CODE_DIR)plane.cpp $(CFLAGS)

load.o: $(CODE_DIR)load.cpp
	$(CC) $(CODE_DIR)load.cpp $(CFLAGS)

updateNPC.o: $(CODE_DIR)updateNPC.cpp
	$(CC) $(CODE_DIR)updateNPC.cpp $(CFLAGS)

singlePlayerGame.o: $(CODE_DIR)singlePlayerGame.cpp
	$(CC) $(CODE_DIR)singlePlayerGame.cpp $(CFLAGS)

clean:
	rm -rf *.o