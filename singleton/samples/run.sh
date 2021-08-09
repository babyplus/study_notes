cpp=`ls *cpp`
g++ $cpp && ./a.out
echo "---------------------------"
g++ -D__MULTITHREAD__  -D__ATOMIC_MUTEX__ $cpp -lpthread && ./a.out
echo "---------------------------"
g++ -D__MULTITHREAD__ -D__MEYERS__ $cpp -lpthread && ./a.out
