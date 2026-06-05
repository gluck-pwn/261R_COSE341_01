#ifndef IO_H
#define IO_H

#include "types.h"

void fill_io_entries(IO *io, int io_count, int* request_times, int* burst_times);
void fill_random_io_entries(IO *io, int io_count, int burst);

#endif