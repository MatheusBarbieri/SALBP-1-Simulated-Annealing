#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <unistd.h>

class Solution;

int numberOfTasks;
std::vector<int> taskTimes;
std::vector<std::vector <int>> precedenceOrder;

int cycleTime = 6;
double temperature = 1;
double temperatureLimit = 0.00001;
double decay = 0.9;
int iterations = 100;
int seed = 0;

class Solution{
private:
    std::vector<int> tasks;
    long value;
public:
    Solution();
    explicit Solution(std::vector<int> tasks);
    long getValue() const;
    int evalSolution();
    bool isValidPrecedence();
    bool isValidTimes();
    Solution neighbour();
    void printSolution();
};

Solution::Solution(){
    std::vector<int> initialSolution((unsigned long)numberOfTasks);
    for(int i=0; i<numberOfTasks; i++){
        initialSolution[i] = i;
    }
    tasks = initialSolution;
    value = evalSolution();
}

Solution::Solution(std::vector<int> tasks){
    this->tasks = std::move(tasks);
    value = evalSolution();
}

void Solution::printSolution() {
    std::cout << "Best value: " << getValue() << std::endl;
    std::cout << "Solution:" << std::endl;
    for(int i=0; i<numberOfTasks; i++)
        std::cout << "\tTask " << i << " on station " << tasks[i] << std::endl;
    std::cout << std::endl;
}

int Solution::evalSolution(){
    std::vector<int> v(tasks);
    std::sort(v.begin(), v.end());
    long count = std::unique(v.begin(), v.end()) - v.begin();
    return (int) count;
}

bool Solution::isValidPrecedence(){
    for (auto &i : precedenceOrder) {
        if(tasks[i[0]] >= tasks[i[1]]){
            return false;
        }
    }
    return true;
}

bool Solution::isValidTimes(){
    std::vector<int> stationTimes(numberOfTasks, 0);
    for (int i=0; i<numberOfTasks; i++) {
        stationTimes[tasks[i]] += taskTimes[i];
        if (stationTimes[tasks[i]] > cycleTime){
            return false;
        }
    }
    return true;
}

bool acceptWorseSolution(){
    float zeroToOne = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1.0));
    return temperature > zeroToOne;
}

Solution Solution::neighbour(){
    while(true) {
        std::vector<int> newTasks(tasks);
        long location = rand() % numberOfTasks;
        long newStation = rand() % numberOfTasks;
        //newTasks[location] += (rand() % 2 ? 1 : -1);
        newTasks[location] = newStation;
        Solution neigh(newTasks);
        if (neigh.isValidPrecedence() && neigh.isValidTimes()) {
            return neigh;
        }
    }
}

long Solution::getValue() const {
    return value;
}

void readInstance() {
    int currentValue;
    std::cin >> numberOfTasks;
    for(int i=0; i<numberOfTasks; i++){
        std::cin >> currentValue;
        taskTimes.push_back(currentValue);
    }
    while(std::cin >> currentValue){
        if (currentValue == -1){
            break;
        }
        int predecessor = currentValue;
        int successor;
        std::cin.ignore(1);
        std::cin >> successor;
        std::vector<int> precedence = {predecessor-1, successor-1};
        precedenceOrder.push_back(precedence);
    }
}

void printInstance() {
    std::cout << "tasks: " << numberOfTasks << std::endl;

}

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:i:l:s:")) != -1) {
        switch (opt) {
            case 'c':
                cycleTime = atoi(optarg);
                break;
            case 't':
                temperature = atof(optarg);
                break;
            case 'l':
                temperatureLimit = atof(optarg);
                break;
            case 'd':
                decay = atof(optarg);
                break;
            case 'i':
                iterations = atoi(optarg);
                break;
            case 's':
                seed = atoi(optarg);
                break;
            default:
                std::cout << "Usage:" << argv[0] << "[OPTIONS]...\n";
                std::cout << "\tOPTIONS:\n";
                std::cout << "\t\t-c cycle_time\n";
                std::cout << "\t\t-t temperature\n";
                std::cout << "\t\t-l temperature_limit\n";
                std::cout << "\t\t-d temperature_decay\n";
                std::cout << "\t\t-i iterations\n";
                std::cout << "\t\t-s seed\n";
                exit(EXIT_FAILURE);
                break;

        }
    }

    if (seed == 0) {
        seed = rand();
    }
    srand(seed);
    std::cout << "command to reproduce:" << std::endl;
    std::cout << argv[0];
    std::cout << " -c " << cycleTime;
    std::cout << " -t " << temperature;
    std::cout << " -l " << temperatureLimit;
    std::cout << " -d " << decay;
    std::cout << " -i " << iterations;
    std::cout << " -s " << seed;
    std::cout << "\n\n";
    std::cout << "Random seed: " << seed << std::endl;

    readInstance();
    srand((u_int) seed);

    Solution currentSolution;
    Solution best = currentSolution;

    while(temperature > temperatureLimit){
        for(int i=0; i<iterations; i++){
            Solution neighbour = currentSolution.neighbour();
            if(neighbour.getValue() < currentSolution.getValue()){
                currentSolution = neighbour;
            } else {
                if(acceptWorseSolution()){
                    currentSolution = neighbour;
                }
            }
            if(neighbour.getValue() < best.getValue()){
                best = neighbour;
            }
        }
        temperature *= decay;
    }

    best.printSolution();
    return 0;
}
