bin:=HornsAlgorithm

$(bin):main.c
	gcc -o main main.c -Wall -std=c99 -lm

clean:
	@rm main