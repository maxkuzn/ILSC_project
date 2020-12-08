# ILSC_project

Project for the course Introduction to Linux and Supercomputers.  


# Installation
```
# Checkout library
$ git clone --recursive https://github.com/maxkuzn/ILSC_project.git
# Go to root directory
$ cd ILSC_project
# Create directory for build
$ mkdir build && cd build
# Generate Makefiles
$ cmake ../
# Build library
$ make
```

# Run tests and benchmarks
```
# From root directory
$ ./build/tests/bin/<test_name>
$ ./build/benchmarsk/bin/<benchmark_name>
```
