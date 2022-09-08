#include <iostream>
#include <vector>
#include <random>
using namespace std;

template <typename T>
using vec1D = vector<T>;


class SimulatedAnnealing{
    public:
        SimulatedAnnealing(int run, int iteration, int bits, double temperature, double decrease):
        total_run(run), total_iteration(iteration), total_bits(bits), init_temperature(temperature), T_decrease(decrease)
        {
            random_device rd;
            random_generator.seed(rd());
            onemax_runbest.assign(total_run, 0);
            onemax_iterbest.assign(total_iteration + 1, 0);
        }
        void Alg_run(){
            for(int i = 0; i < total_run; ++i){
                current_best = 0;
                double t = init_temperature;
                vec1D<int> solution(total_bits, 0);
                int sum = init(solution);
                onemax_iterbest[0] += current_best;
                for(int j = 0; j < total_iteration; ++j){
                    vec1D<int> next = transition(solution);
                    int next_sum = evaluation(next);
                    determine(solution, sum, next, next_sum, t);
                    onemax_iterbest[j + 1] += current_best;
                }
                onemax_runbest[i] = current_best;
                // cout << current_best << endl;
            }


            for(size_t i = 0; i < onemax_iterbest.size(); ++i){
                cout << (double) onemax_iterbest[i] / total_run << endl;  
            }
        }
    private:
        int total_run;
        int total_iteration;
        int total_bits;
        double init_temperature;
        double T_decrease;
        int current_best;
        vec1D<int> onemax_runbest;
        vec1D<int> onemax_iterbest;
        mt19937_64 random_generator;

        int random_int(const int min, const int max){
            uniform_int_distribution<int> dis(min, max);
            return dis(random_generator);
        }
        double random_real(const double min, const double max){
            uniform_real_distribution<double> dis(min, max);
            return dis(random_generator);
        }
        int init(vec1D<int> &solution){
            for(size_t i = 0; i < solution.size(); ++i){
                solution[i] = random_int(0, 1);
            }
            int value = evaluation(solution);
            if(value > current_best) current_best = value;
            return value;
        }
        int evaluation(const vec1D<int> &sol){
            int sum = 0;
            for(size_t i = 0; i < sol.size(); ++i){
                if(sol[i]){
                    ++sum;
                }
            }
            return sum;
        }
        vec1D<int> transition(const vec1D<int> &curr_sol){
            vec1D<int> next_solution = curr_sol;
            int rnd = random_int(0, total_bits - 1);
            if(next_solution[rnd]) next_solution[rnd] = 0;
            else next_solution[rnd] = 1;

            return next_solution;
        }
        void determine(vec1D<int> &curr_sol, int &curr_sum, vec1D<int> &next_sol, int &next_sum, double &t){
            if(next_sum >= curr_sum){
                curr_sum = next_sum;
                curr_sol = next_sol;

                if(next_sum > current_best) current_best = next_sum;
            }
            else{
                double rnd = random_real(0.0, 1.0);
                if(rnd < exp((next_sum - curr_sum) / t)){
                    curr_sum = next_sum;
                    curr_sol = next_sol;
                }
            }

            t *= T_decrease;
        }
};