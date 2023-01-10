#ifndef READER_H
#define READER_h

long double** ReadFile(const char* fileName, int* outRowCount, int* outColumnCount);

double* ReadTestLine(const char* fileName);

#endif
