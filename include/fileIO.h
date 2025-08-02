#ifndef FILE_IO_H
#define FILE_IO_H

int read_config(const char *filename, cosmology *params);
flux* read_fluxes(const char* filename, int* count);

#endif // !FILE_IO_H
