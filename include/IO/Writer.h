#ifndef WRITER_H
#define WRITER_H

void WriteFile(const char* fileName, long double** values, int counti, int countj);

void WritePlotFile(const char* fileName, const char* dataFileName, const char* outFileName, int rowCount, int columnCount);

#endif
