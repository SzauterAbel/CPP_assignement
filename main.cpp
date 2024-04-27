#include <iostream>
#include <chrono>
#include <functional>
#include <queue>
#include <fstream>
#include "date.hpp"

typedef int (*DateProcessor)(const Date&);
DateProcessor consumer = &process_date;

template<typename Func>
auto measure_execution_time(const std::string& task_name, Func&& task) {
    auto start = std::chrono::steady_clock::now();
    std::cerr << task_name << " task has started." << std::endl;
    task();
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cerr << task_name << " task was finished in " << duration << " millisec." << std::endl;
}

auto read_dates_from_file = [](std::ifstream *inputFile, int* N, int* K, std::vector<Date> *dateVector,
    std::priority_queue<Date, std::vector<Date>, std::greater<Date>> *datePriorityQueue){
        (*inputFile) >> *N >> *K;
        if (*N < 0 || *K < 0) {
            std::cerr << "Error: N and K must be non-negative" << std::endl;
            return;
        }

        
        for (int i = 0; i < *N; ++i) {
            short year, month, day;
            (*inputFile) >> year >> month >> day;
            datePriorityQueue->push(Date(year, month, day));
        }

        for (int i = 0; i < *K; ++i) {
            short year, month, day;
            (*inputFile) >> year >> month >> day;
            dateVector->push_back(Date(year, month, day));
        }
        (*inputFile).close();
    };


auto choose_delete_replace = [](int N, int K, std::vector<Date> *dateVector,
    std::priority_queue<Date, std::vector<Date>, std::greater<Date>> *datePriorityQueue) {
    for (int i = 0; i < N + K; ++i) {
        Date minDate = datePriorityQueue->top();
        consumer(minDate);
        datePriorityQueue->pop();

        if (i < K) {
            datePriorityQueue->push(dateVector->at(i));
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }
    
    int N, K;
    std::vector<Date> dateVector;
    std::priority_queue<Date, std::vector<Date>, std::greater<Date>> datePriorityQueue;

    
    measure_execution_time("Read dates from file",
        [&inputFile, &N, &K, &dateVector, &datePriorityQueue](){
            read_dates_from_file(&inputFile, &N, &K, &dateVector, &datePriorityQueue);
    });

    measure_execution_time("Choose, remove, replace",
    [&inputFile, &N, &K, &dateVector, &datePriorityQueue](){
        choose_delete_replace(N, K, &dateVector, &datePriorityQueue);
    });

    return 0;
}