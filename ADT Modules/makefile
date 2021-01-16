output:App_StringADT.o stringADT.o
	gcc App_StringADT.o stringADT.o -o output

App_StringADT.o: App_StringADT.c
	gcc -c App_StringADT.c

stringADT.o: stringADT.c stringADT.h
	gcc -c stringADT.c 

clean:
	del *.o output.exe