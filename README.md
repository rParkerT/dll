Implementation of the ordered Doubly Linked List. Doubly Linked List is a linear
collection of data elements in which every element points to the next and previous element.

CMake is used for project build. For building tests for testDLL.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList. Doxygen is used for project documentation.

To build project and project documentation, go to root directory:
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc

To run tests:
$ cd test
$ ./tests

To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests

Benchmark results:

-------------------------------------------------------------------------------
Doubly Linked List insert and search - Benchmark
-------------------------------------------------------------------------------
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Add 100.000 nodes in Doubly Linked
List                                           100             1     1.33839 s
                                        13.5502 ms    13.4398 ms    13.7277 ms
                                        702.527 us    494.281 us    996.442 us

Search 100 nodes in Doubly Linked
List of 100.000 nodes                          100             1     4.40006 s
                                        44.8145 ms    43.9176 ms    45.9953 ms
                                        5.21421 ms    4.24972 ms    6.19041 ms
