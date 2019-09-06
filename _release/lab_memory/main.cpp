/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    std::cout << std::endl;

    fileio::init();
    std::cout << "TIHS IS 1" << std::endl;
    Allocator theAllocator("students.txt", "rooms.txt");
    std::cout << "TIHS IS 2" << std::endl;
    theAllocator.allocate();
    std::cout << "TIHS IS 3" << std::endl;
    theAllocator.printRooms();
    std::cout << "TIHS IS 4" << std::endl;
    fileio::halt();

    std::cout << std::endl;
    return 0;
}
