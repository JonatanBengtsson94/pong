build:
	@mkdir -p ./build
	g++ -o ./build/pong *.cpp -lSDL2
run:
	./pong
clean:
	rm -rf ./build
