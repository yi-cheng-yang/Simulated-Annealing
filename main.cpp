#include "SA.h"


int main(int argc, char* argv[]){
    int run = atoi(argv[1]);
    int iteration = atoi(argv[2]);
    int bits = atoi(argv[3]);
    double temperature = atof(argv[4]);
    double decrease = atof(argv[5]);

    SimulatedAnnealing alg(run, iteration, bits, temperature, decrease);
    alg.Alg_run();
}