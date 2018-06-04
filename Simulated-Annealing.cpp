#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

int numberOfTasks;
std::vector<int> taskTimes;
std::vector<std::vector <int>> precedenceOrder;

class Solution{
private:
    std::vector<int> tasks;

public:
    Solution();
    int evalSolution();
    bool validatePrecedence();
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

}

bool Solution::validatePrecedence(){

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
        inputFileName = argv    [1];
    }

    readFile(inputFileName);

    return 0;
}
