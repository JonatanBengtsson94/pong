build:
	@mkdir -p ./build
	g++ -Wall -o ./build/pong *.cpp -lSDL2
run:
	./build/pong
clean:
	rm -rf ./build
