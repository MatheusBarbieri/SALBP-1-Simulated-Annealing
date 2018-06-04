#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

int numberOfTasks;
std::vector<int> taskTimes;
std::vector<std::vector <int>> precedenceOrder;

class Solution{
private:
    std::vector<int> tasks;

public:
    Solution();
    int evalSolution();
    bool isValidPrecedence();
    Solution neighboor();
    void printSolution();
};

Solution::Solution(){
    std::vector<int> initialSolution((unsigned long)numberOfTasks);
    for(int i=0; i<numberOfTasks; i++){
        initialSolution[i] = i;
    }
    tasks = initialSolution;
}

void Solution::printSolution() {
    for(int i=0; i<numberOfTasks; i++)
        std::cout << tasks[i] << " ";
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

Solution Solution::neighboor(){

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
    std::string inputFileName;

    if (argc < 7){
        std::cout << "Incorret Usage! Correct Usage:\n\t"
                     "./simulated-annealing <inputfile> <temperature> <decay>"
                     " <iterations-before-decay> <limit-temperature> <seed>" << std::endl;
        return -1;
    } else {
        inputFileName = argv[1];
    }

    readFile(inputFileName);
    return 0;
}
