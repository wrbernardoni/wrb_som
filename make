g++ -c wrb_som.cpp -std=c++11
ar rvs wrb_som.a wrb_som.o
rm wrb_som.o

g++ -Wall -Wextra -o ./build/wrb_som.exe main.cpp wrb_som.a -std=c++11

