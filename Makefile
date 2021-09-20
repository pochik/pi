all: main.c
	gcc main.c -o main -pthread
	./main 1000000 4
	rm main
test:
	gcc main.c -o main -pthread -fsanitize=address
	bash test.sh
