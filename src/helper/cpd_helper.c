#include <stdio.h>
#include <CPDFrontend.h>

int main(int argc , char **argv)
{
    if(argc != 2)
    {
        printf("Usage : %s filepath_to_print\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    char pickle_file[256];
    snprintf(pickle_file, sizeof(pickle_file), "%s%s%s", "/tmp/", argv[1], ".pickle");

    char data_file[256];
    snprintf(data_file, sizeof(pickle_file), "%s%s%s", "/tmp/", argv[1], ".pdf");

    printf("%s\n", pickle_file);
    printf("%s\n", data_file);
    PrinterObj *p = resurrect_printer_from_file(pickle_file);
    print_file(p, data_file);
}
