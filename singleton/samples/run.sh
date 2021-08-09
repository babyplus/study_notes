cpp=`ls *cpp`
g++ -I "../../common/" $cpp && ./a.out
echo "---------------------------"
g++ -I "../../common/" -D__MULTITHREAD__  -D__ATOMIC_MUTEX__ $cpp -lpthread && ./a.out
echo "---------------------------"
g++ -I "../../common/" -D__MULTITHREAD__ -D__MEYERS__ $cpp -lpthread && ./a.out

