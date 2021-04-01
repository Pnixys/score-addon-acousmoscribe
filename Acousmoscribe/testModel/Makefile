test: testModel.o ../Model/Sign.o
		g++ -o test test.o Sign.o

test.o: testModel.cpp testModel.hpp ../Model/Sign.hpp
		g++ -Wall -c __Test.cpp

Sign.o: ../Model/Sign.cpp ../Model/Sign.hpp
		g++ -Wall -c ../Model/Sign.cpp

clean:
		rm -f *.o