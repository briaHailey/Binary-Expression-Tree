# Rule to build the executable
proj3.mine.x: proj3_driver.o bet.o
	g++ -std=c++11 -o proj3.mine.x proj3_driver.o bet.o

# Rules to build object files
proj3_driver.o: proj3_driver.cpp bet.h
	g++ -std=c++11 -c proj3_driver.cpp -o proj3_driver.o

bet.o: bet.cpp bet.h
	g++ -std=c++11 -c bet.cpp -o bet.o

# Clean rule
clean:
	rm -f *.o proj3.mine.x
