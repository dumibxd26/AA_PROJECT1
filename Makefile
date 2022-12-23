
start: build

run-p1:
	./runDijkstraPQ.exe

run-p2:
	./runDijkstraWoPQ.exe

run-p3:
	./runBFQ.exe

run-p4:
	./runBFQWOQ.exe

run-p5:
	./runDial.exe

run-best:
	./runDijkstraPQ.exe

build:
	g++ BellmanFordQueue.cpp -o BellmanFordQueue.exe
	g++ BellmanFOrdWoQueue.cpp -o BellmanFOrdWoQueue.exe
	g++ DijkstraPQ.cpp -o DijkstraPQ.exe
	g++ DijkstraWoPQ.cpp -o DijkstraWoPQ.exe
	g++ Dial.cpp -o Dial.exe
	g++ runBFQ.cpp -o runBFQ.exe
	g++ runBFWOQ.cpp -o runBFWOQ.exe
	g++ runDial.cpp -o runDial.exe
	g++ runDijkstraPQ.cpp -o runDijkstraPQ.exe
	g++ runDijkstraWoPQ.cpp -o runDijkstraWoPQ.exe

clean: 
	rm BellmanFordQueue.exe

.PHONY: clean
