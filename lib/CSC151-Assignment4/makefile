all: Parser Scanner YourCode
	gcc BabyC.tab.o lex.yy.o driver.o node_actions.o symbol_table.o -o bcc

YourCode: symbol_table.o node_actions.o driver.o 

Scanner: BabyC.lex 
	flex BabyC.lex
	gcc -c lex.yy.c

Parser: BabyC.y  
	bison -d BabyC.y
	gcc -c BabyC.tab.c

clean: 
	rm -f *.o *.out

test:
	./bcc test1.bc > test1.out
	./bcc test2.bc > test2.out
	./bcc test3.bc > test3.out
	./bcc test4.bc > test4.out
	./bcc test5.bc > test5.out
	./bcc test6.bc > test6.out
	diff test1.out test1_result.txt
	diff test2.out test2_result.txt
	diff test3.out test3_result.txt
	diff test4.out test4_result.txt
	diff test5.out test5_result.txt
	diff test6.out test6_result.txt

%.o: %.c 
	gcc -c $<

