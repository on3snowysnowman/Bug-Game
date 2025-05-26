#include <vector>
#include <iostream>
#include <thread>
#include <cstdint>

#include "OreMine.hpp"
#include "TimeObserver.hpp"
#include "Sector.hpp"

struct TickFunctionWrapper
{
    void (*fn)(void*) {};
    void* obj_instance {};
};

void parse_segment(const std::vector<TickFunctionWrapper>& tick_functions, 
    int start, int end)
{
    for(int i = start; i < end; ++i)
    {
        tick_functions.at(i).fn(tick_functions.at(i).obj_instance);
    }
}


int main()
{
    c_time_point start, end;

    Sector s;

    OreMine ore_mine(&s);

    std::vector<TickFunctionWrapper> tick_functions;

    constexpr int ITERATIONS = 1000000;

    for(int i = 0; i < ITERATIONS; ++i)
        tick_functions.push_back({OreMine::tick_thunk, &ore_mine});

    start = TimeObserver::get_time_point();

    for(const TickFunctionWrapper& wrapper : tick_functions)
    {
        wrapper.fn(wrapper.obj_instance);
    }

    end = TimeObserver::get_time_point();

    std::cout << "No threading: " << 
        TimeObserver::calculate_interval_from_timepoints(start, end) << '\n';

    uint8_t num_threads = std::thread::hardware_concurrency(); 

    std::vector<std::thread> threads;

    int segment_size = ITERATIONS / num_threads;

    int i = 0;

    start = TimeObserver::get_time_point();
    
    while(i < num_threads - 1)
    {
        int segment_start = i * segment_size;
        int segment_end = segment_start + segment_size;
        threads.emplace_back(parse_segment, tick_functions, segment_start, 
            segment_end);
        ++i;
    }

    // Add last thread, ensuring it spans the rest of the tick functions
    int segment_start = i * segment_size;
    int segment_end = ITERATIONS;
    threads.emplace_back(parse_segment, tick_functions, segment_start, 
        segment_end);

    for(std::thread& thread : threads) thread.join();

    end = TimeObserver::get_time_point();

    std::cout << "With threading: " << 
        TimeObserver::calculate_interval_from_timepoints(start, end) << '\n';

    return 0;
}

