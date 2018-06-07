#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility> #include <vector>

class Solution;

int numberOfTasks, cycleTime, iterations, seed;
double temperature, decay, temperatureLimit;
std::vector<int> taskTimes;
std::vector<std::vector <int>> precedenceOrder;
std::string inputFileName;


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
        newTasks[location] += (rand() % 2 ? 1 : -1);
        Solution neigh(newTasks);
        if (neigh.isValidPrecedence() && neigh.isValidTimes()) {
            return neigh;
        }
    }
}

long Solution::getValue() const {
    return value;
}

void readFile(std::string &fileName){
    std::ifstream file;
    file.open(fileName);
    int currentValue;
    file >> numberOfTasks;
    for(int i=0; i<numberOfTasks; i++){
        file >> currentValue;
        taskTimes.push_back(currentValue);
    }
    while(file >> currentValue){
        if (currentValue == -1){
            break;
        }
        int predecessor = currentValue;
        int successor;
        file.ignore(1);
        file >> successor;
        std::vector<int> precedence = {predecessor-1, successor-1};
        precedenceOrder.push_back(precedence);
    }
    file.close();
}

int main(int argc, char **argv) {
    if (argc < 8){
        std::cout << "Incorret Usage! Correct Usage:\n\t"
                     "./salbp1-sa <inputfile> <cycle-time> <temperature> <decay>"
                     " <iterations-before-decay> <limit-temperature> <seed>" << std::endl;
        return -1;
    } else {
        inputFileName = argv[1];
        cycleTime = atoi(argv[2]);
        temperature = atof(argv[3]);
        decay = atof(argv[4]);
        iterations = atoi(argv[5]);
        temperatureLimit = atof(argv[6]);
        seed = atoi(argv[7]);
    }

    readFile(inputFileName);
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
