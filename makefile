#makefile

s:
	gcc -Wall  L1.c L2.c L3.c main_s.c -g -o S

c:
	gcc -Wall L1.c L2.c L3.c main_c.c -g -o C
clean:
	rm S
	rm C
