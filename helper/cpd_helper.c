#include <stdio.h>
#include <CPDFrontend.h>

int main(int argc , char **argv)
{
    if(argc != 2)
    {
        printf("Usage : %s uniqueID\n", argv[0]);
        return EXIT_FAILURE;
    }
    char pickle_file[256];
    snprintf(pickle_file, sizeof(pickle_file), "%s%s%s", "/tmp/", argv[1], ".pickle");

    char data_file[256];
    snprintf(data_file, sizeof(pickle_file), "%s%s%s", "/tmp/", argv[1], ".pdf");

    FILE *file;

    file = fopen(pickle_file, "r");
    if (file) {
        fclose(file);
    }
    else {
        perror(pickle_file);
        return EXIT_FAILURE;
    }

    file = fopen(data_file, "r");
    if (file) {
        fclose(file);
    }
    else {
        perror(data_file);
        return EXIT_FAILURE;
    }

    PrinterObj *p = resurrect_printer_from_file(pickle_file);
    print_file(p, data_file);

    return EXIT_SUCCESS;
}
