#ifndef READER_H
#define READER_h

/// @brief Reads all values from a file.
/// @param fileName Name of the file which gets read.
/// @param outRowCount The row count of the matrix.
/// @param outColumnCount The column count of the matrix.
/// @return The values as a double matrix.
double** ReadFile(const char* fileName, int* outRowCount, int* outColumnCount);

/// @brief Reads one line from a file.
/// @param fileName Name of the file which gets read.
/// @return The values as a double array.
double* ReadTestLine(const char* fileName);

#endif
