
test: test.o flood.o
	g++ -o $@ $^

test.o: test.cpp
	g++ -c -o $@ $<

flood.o: flood.cpp flood.h
	g++ -c -o $@ $<

clean:
	$(RM) test *.o
