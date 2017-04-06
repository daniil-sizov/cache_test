#Cache Test

This is small project for study purposes.

## Building

mkdir build
cmake <path_to_repo_dir>
make
cd cache_test

## Running the tests

chmod +x scripts
./scripts/run_all.sh

## Usage

	./cache_test [OPTIONS] TEST_SEQUENCE_FILE

### Options
	-h,    show help
	-v,    show extra statistics
	-l,    show legend and table header
	-m,    set memory size (in bytes)
	-c,    set cache size (in bytes)
	-b,    set block size (in bytes)
	-a,    set associativity
	-i,    set cache access time (in ns)
	-s,    set memory access time (in ns)
	-w,    set writing policy (write-through or write-back)
	-r,    set replacement policy (LRU, LFU or FIFO)
