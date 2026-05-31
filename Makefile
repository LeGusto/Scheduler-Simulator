all: src/fifo.cpp src/main.cpp src/policy.cpp src/sjf.cpp src/stcf.cpp src/robin.cpp
	g++ src/fifo.cpp src/main.cpp src/policy.cpp src/sjf.cpp src/stcf.cpp src/robin.cpp -I. -o ./bin/main