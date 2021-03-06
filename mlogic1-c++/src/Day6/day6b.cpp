/************************  ADVENT OF CODE 2017 **********************************       *
**                                                                              *      /.\
**                         adventofcode.com                                     *     /..'\
**                                                                              *     /'.'\
**                         mlogic1 (https://github.com/mlogic1)                 *    /.''.'\
**                                                                              *    /.'.'.\
**                                                                              *   /'.''.'.\
**                         Day 6 - Memory Reallocation                          *   ^^^[_]^^^
**                                                                              *
**                                                                              *
**                                                                              *
********************************************************************************/


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;



int BiggestNumberIndex(const vector<int> numbers){
    int biggestNumber = 0;
    int biggestNumberIndex = 0;

    for(int i=0;i<numbers.size();i++){
        if(numbers[i] > biggestNumber){
            biggestNumber = numbers[i];
            biggestNumberIndex = i;
        }
    }
    return biggestNumberIndex;
}

int Cycles_Day6b(vector<int> input){
    int n = input.size();           // number of blocks
    int cycles = 0;
    vector< vector<int> > seen_vectors;       // contains all the seen memory vectors

    // add the starting vector to seen vectors
    seen_vectors.push_back(input);


    vector<int> first_duplicate;
    bool first_seen_found = false;
    int cycles_after_first_duplicate = 0;


    while(true){
        // find the biggest number
        int index = BiggestNumberIndex(input);
        int value = input[index];
        input[index] = 0;

        while(value > 0){
            // iterate the array until you run of numbers
            index++;

            if(index >= n){
                index = 0;
            }

            input[index]++;
            value--;
        }

        cycles++;


        if(!first_seen_found){
            for(int i = 0;i<seen_vectors.size();i++){
                if(seen_vectors[i] == input){
                    first_seen_found = true;
                    first_duplicate = input;
                }
            }
        }else{

            int foundCounter = 0;
            cycles_after_first_duplicate++;
            for(int i = 0;i<seen_vectors.size();i++){
                if(seen_vectors[i] == input){
                    foundCounter++;
                }
            }

            if(foundCounter >= 2){
                return cycles_after_first_duplicate;
            }
        }

        seen_vectors.push_back(input);

    }

    return 0;
}


vector<int> ReadFromFile(const char* fileName){
    ifstream input(fileName, ifstream::in);
    vector<int> data;
    string line = "";
    if(!input){
        return data;
    }

    while(!input.eof()){
        getline(input,line);
        if(line == ""){
            break;
        }
        // read numbers separated by spaces or tabs and add them to the vector
        stringstream strm(line);
        int number;
        while(true){
            strm >> number;
            if(!strm){
                break;
            }
            data.push_back(number);
        }
    }

    input.close();
    return data;
}

int main(){
    vector<int> input = ReadFromFile("../../inputs/day6.txt");
    if(input.size() < 1){
        return -1;
    }
    unsigned int result6b = Cycles_Day6b(input);
    cout<<"Problem 6b result: "<<result6b<<endl;

    return 0;
}

