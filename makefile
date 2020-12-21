project3: project3.cpp avltree.cpp
	g++ -std=c++11 project3.cpp avltree.cpp -o project3.out

test: test.cpp avltree.cpp
	g++ -std=c++11 test.cpp avltree.cpp -o test.out

clean:
	rm -f *.out main
