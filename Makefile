SRC:=src
BLD:=build

$(shell  mkdir -p $(BLD))

all: writer reader

writer: writer.o
	g++ $(BLD)/writer.o -o $(BLD)/writer

writer.o: $(SRC)/writer.cpp
	g++ -c $(SRC)/writer.cpp -o $(BLD)/writer.o

reader: reader.o
	g++ $(BLD)/reader.o -o $(BLD)/reader

reader.o: $(SRC)/reader.cpp
	g++ -c $(SRC)/reader.cpp -o $(BLD)/reader.o

clean:
	rm -rf $(BLD)