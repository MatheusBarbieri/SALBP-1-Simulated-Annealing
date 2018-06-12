#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <utility>
#include <vector>

//Instance parameters
int numberOfTasks;
int cycleTime = 6;
std::vector<int> taskTimes;
std::vector<std::vector <int>> precedenceOrder;

//Simulated Annealing Parameters
double temperature = 1;
double initialTemperature = 1;
double temperatureLimit = 0.00001;
double decay = 0.9;
int iterations = 1000;
long seed = 0;

//misc
bool verbose = false;


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
    void printSimple();
    void generateInitialSolition_v1();
    void generateInitialSolition_v2();
};

Solution::Solution(){
    generateInitialSolition_v2();
    value = evalSolution();
}

Solution::Solution(std::vector<int> tasks){
    this->tasks = std::move(tasks);
    value = evalSolution();
}


void Solution::generateInitialSolition_v1(){
    tasks = std::vector<int>((unsigned long)numberOfTasks);
    std::cout << "generating initial solution v1" << '\n';
    for (int i=0; i<numberOfTasks; i++) {
        tasks[i] = i;
    }
}

void Solution::generateInitialSolition_v2(){
    tasks = std::vector<int>((unsigned long)numberOfTasks);
    std::cout << "generating initial solution v2" << '\n';
    int si = 0;
    int ci = 0;
    for (int i=0; i<numberOfTasks; i++) {
        if (ci + taskTimes[i] <= cycleTime) {
            ci += taskTimes[i];
            tasks[i] = si;
        } else {
            ci = taskTimes[i];
            tasks[i] = ++si;
        }
    }
}

int Solution::evalSolution(){
    std::vector<int> v(tasks);
    std::sort(v.begin(), v.end());
    long count = std::unique(v.begin(), v.end()) - v.begin();
    return (int) count;
}

bool Solution::isValidPrecedence(){
    for (auto &i : precedenceOrder) {
        if(tasks[i[0]] > tasks[i[1]]){
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
        newTasks[location] = (int) newStation;
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

void printPrecedence(){
    auto size = (long) ceil(sqrt(precedenceOrder.size()));
    std::cout << "Precedence Order:" << std::endl;
    int i=1;
    for(auto item : precedenceOrder){
        std::cout << "\t" << item[0]+1 << "->" << item[1]+1;
        if (i % size == 0){
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
        i++;
    }
}

void printTimes(){
    auto size = (long) ceil(sqrt(numberOfTasks));
    std::cout << "Task times:";
    for(int i=0; i<numberOfTasks; i++){
        if (i % size == 0){
            std::cout << std::endl;
        }
        std::cout << "\t(" << i+1 << ")" << taskTimes[i] << "u.t.";
    }
}

void printInstance() {
    std::cout << "\n################### Instance ###################\n";
    std::cout << "Seed: " << seed << std::endl;
    std::cout << "Number of tasks: " << numberOfTasks << std::endl;
    std::cout << "Cycle time: " << cycleTime << std::endl;
    printPrecedence();
    std::cout << std::endl;
    printTimes();
    std::cout << std::endl;
}

void printParameters(){
    std::cout << "Parameters to reproduce this execution:" << std::endl;
    std::cout << "\t-c " << cycleTime;
    std::cout << " -t " << initialTemperature;
    std::cout << std::fixed;
    std::cout << " -l " << temperatureLimit;
    std::cout << " -d " << decay;
    std::cout << " -i " << iterations;
    std::cout << " -s " << seed;
    std::cout << std::endl;
}

void Solution::printSimple(){
    std::cout << "Seed: " << seed << std::endl;
    std::cout << "Number of tasks: " << numberOfTasks << std::endl;
    std::cout << "Cycle time: " << cycleTime << std::endl;
    std::cout << "Best value: " << getValue() << std::endl;
}

void Solution::printSolution() {
    std::cout << "\n################### Solution ###################\n";
    std::cout << "Best value: " << getValue() << std::endl;

    std::cout << "Used Stations: " << std::endl;
    std::vector<std::vector<int> > stations((u_long)numberOfTasks);
    for(int i=0; i<numberOfTasks; i++){
        stations[tasks[i]].push_back(i);
    }
    int count = 0;

    for(auto& station : stations){
        if (station.size()){
            std::cout << "\tStation " << ++count << " tasks:";
            for(auto& task : station){
                std::cout << " " << task+1 << ((&task==&station.back())?"\n":",");
            }
        }
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:i:l:s:v")) != -1) {
        switch (opt) {
            case 'c':
                cycleTime = atoi(optarg);
                break;
            case 't':
                temperature = atof(optarg);
                initialTemperature = temperature;
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
            case 'v':
                verbose = true;
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
                std::cout << "\t\t-v verbose\n";
                exit(EXIT_FAILURE);
                break;
        }
    }

    if (seed == 0) {
        seed = (time(NULL));;
    }
    srand(static_cast<unsigned int>(seed));
    readInstance();
    srand((u_int) seed);

    Solution currentSolution;
    Solution best = currentSolution;

    long loopCount = 0;
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
        if (verbose)
            std::cout << "." << std::flush;
    }
    std::cout << std::endl;
    //print outputs
    if (verbose){
        printInstance();
        best.printSolution();
        printParameters();
    } else {
        best.printSimple();
    }

    return 0;
}
