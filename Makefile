make:
	clang main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o dll
	./dll
