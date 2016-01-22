#include "stdafx.h"
#include "tools.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <pthread.h>


const int loops = 150000000;
volatile int count = 0;


std::string current_thread_id() {
	pthread_t tid = pthread_self();
	std::stringstream ss;
	ss << tid.p;
	return ss.str();
}


void *threadFunction(void *p_arg)
{
	int number = reinterpret_cast<int>( p_arg );
	int wait = 2 + rand() % 7;
	std::cout << "- thread " << current_thread_id() << " started with number " << number << " and is waiting for " << wait << " seconds." << std::endl;
	sleep( wait );
	std::cout << "- threadFunction " << current_thread_id() << " is ending with number " << number << std::endl;
	return nullptr;
}


int main(int argc, char *argv[])
{
	int count = 0;
	pthread_t *tid = nullptr;

	// Get thread count from command line
	if ( argc < 2 ) {
		std::cerr << "** Invalid parameter count." << std::endl;
		return EXIT_FAILURE;
	}
	count = std::atoi( argv [ 1 ] );

	// Create threads
	std::cout << "Starting " << count << " threads." << std::endl;
	tid = new pthread_t [count];
	for ( int i = 0; i < count; i++ ) {
		std::cout << "** Creating thread #" << i << "..." << std::endl;
		if ( pthread_create( &tid[i], nullptr, threadFunction, reinterpret_cast<void *>(i) ) != 0 ) {
			std::cerr << "** FAIL" << std::endl;
			return EXIT_FAILURE;
		}
	}

	std::cout << "** Waiting for threads to end..." << std::endl;
	sleep(3);

	// Join threads
	for ( int i = 0; i < count; i++ ) {
		pthread_join( tid [ i ], nullptr );
	}
	delete[] tid;

	std::cout << "** Goodbye" << std::endl;
	return EXIT_SUCCESS;
}
