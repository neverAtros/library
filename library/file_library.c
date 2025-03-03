#include <Windows.h>
#include <stdio.h>

__declspec(dllexport) FILE* open_file(const char* path) {
    FILE* file = fopen(path, "a+");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file at %s\n", path);
    }
    return file;
}

__declspec(dllexport) void close_file(FILE* file) {
    if (file && fclose(file) != 0) {
        fprintf(stderr, "Error closing the file.\n");
    }
}

__declspec(dllexport) void write_file(FILE* file, const char* data) {
    if (file) {
        if (fputs(data, file) == EOF) {
            fprintf(stderr, "Error writing to file.\n");
        }
        else {
            fflush(file);
        }
    }
    else {
        fprintf(stderr, "File is not opened for writing.\n");
    }
}

__declspec(dllexport) void read_file(FILE* file, char* buffer, size_t size) {
    if (file) {
        fseek(file, 0, SEEK_SET);
        if (fgets(buffer, size - 1, file) == NULL) { 
            fprintf(stderr, "Error reading from file.\n");
        }
    }
    else {
        fprintf(stderr, "File is not opened for reading.\n");
    }
}