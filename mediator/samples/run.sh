cpp=`ls *cpp`
g++ -I "../../common/" $cpp -lpthread && ./a.out
