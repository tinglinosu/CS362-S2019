CFLAGS = -Wall -fpic -coverage -lm -std=c99

testme:
	gcc -o testme -g testme.c $(CFLAGS)
	-./testme
	gcov testme.c >testme.out

clean:
	rm testme *.gcda *.gcno *.gcov testme.out
