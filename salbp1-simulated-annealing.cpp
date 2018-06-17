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
#include <chrono>

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
int restarts = 1;
long seed = 0;

//misc
bool verbose = false;
bool csv = false;

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
    void printSimple(float duration);
    void printCsv(float duration);
    void generateInitialSolution();
};

Solution::Solution(){
    generateInitialSolution();
    value = evalSolution();
}

Solution::Solution(std::vector<int> tasks){
    this->tasks = std::move(tasks);
    value = evalSolution();
}

void Solution::generateInitialSolution(){
    tasks = std::vector<int>((unsigned long)numberOfTasks);
    int stationIndex = 0;
    int stationTime = 0;
    for (int i=0; i<numberOfTasks; i++) {
        if (stationTime + taskTimes[i] <= cycleTime) {
            stationTime += taskTimes[i];
            tasks[i] = stationIndex;
        } else {
            stationTime = taskTimes[i];
            tasks[i] = ++stationIndex;
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
    std::cout << "################### Instance ###################\n";
    std::cout << "Seed: " << seed << std::endl;
    std::cout << "Number of tasks: " << numberOfTasks << std::endl;
    std::cout << "Cycle time: " << cycleTime << std::endl;
    printPrecedence();
    std::cout << std::endl;
    printTimes();
    std::cout << std::endl;
}

void printExecution(float duration){
    std::cout << "################### Execution ###################\n";
    std::cout << "Duration: " << duration << " seconds.\n";
    std::cout << "Parameters to reproduce this execution:" << std::endl;
    std::cout << "\t-c " << cycleTime;
    std::cout << " -t " << initialTemperature;
    std::cout << std::fixed;
    std::cout << " -l " << temperatureLimit;
    std::cout << " -d " << decay;
    std::cout << " -i " << iterations;
    std::cout << " -r " << restarts;
    std::cout << " -s " << seed;
    if (verbose){
        std::cout << " -v";
    }
    std::cout << std::endl;
}

void Solution::printSimple(float duration){
    std::cout << "Seed: " << seed << std::endl;
    std::cout << "Number of tasks: " << numberOfTasks << std::endl;
    std::cout << "Cycle time: " << cycleTime << std::endl;
    std::cout << "Best value: " << getValue() << std::endl;
    std::cout << "Execution duration: " << duration << std::endl;
}

void Solution::printCsv(float duration){
    std::cout << seed << "; " <<
                 numberOfTasks << "; " <<
                 cycleTime << "; " <<
                 iterations << "; " <<
                 restarts << "; " <<
                 getValue() << "; " <<
                 duration << ";";
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

void getOptions(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:i:r:l:s:vp")) != -1) {
        switch (opt) {
            case 'c':
                cycleTime = atoi(optarg);
                break;
            case 't':
                temperature = atof(optarg);
                initialTemperature = temperature;
                break;
            case 'r':
                restarts = atoi(optarg);
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
            case 'p':
                csv = true;
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
                std::cout << "\t\t-v (verbose)\n";
                std::cout << "\t\t-p (csv)\n";
                exit(EXIT_FAILURE);
                break;
        }
    }
}

int main(int argc, char **argv) {
    getOptions(argc, argv);

    if (seed == 0) {
        seed = (time(NULL));;
    }

    srand(static_cast<unsigned int>(seed));
    readInstance();

    std::chrono::high_resolution_clock::time_point timeBefore = std::chrono::high_resolution_clock::now();

    Solution currentSolution;
    Solution best = currentSolution;

    for(int res = 0; res < restarts; res++){
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
        }
        temperature = initialTemperature;
        currentSolution = best;
    }

    std::chrono::high_resolution_clock::time_point timeAfter = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeAfter - timeBefore).count();
    auto durationSec = duration/1000000.0;

    //print outputs
    if (csv){
        best.printCsv(durationSec);
    } else {
        if (verbose){
            printInstance();
            best.printSolution();
            printExecution(durationSec);
        } else {
            best.printSimple(durationSec);
        }
    }

    return 0;
}
