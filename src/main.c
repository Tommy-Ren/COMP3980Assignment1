#include "../include/file_transformer.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int         input_fd;
    int         output_fd;
    char        buffer;
    ssize_t     bytes_read;
    filter_func filter = NULL;

    // Command-line argument parsing
    const char *input_file  = NULL;
    const char *output_file = NULL;
    const char *filter_name = NULL;

    int opt;
    while((opt = getopt(argc, argv, "i:o:f:")) != -1)
    {
        switch(opt)
        {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'f':
                filter_name = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -i input_file -o output_file -f filter\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Validate command-line arguments
    if(!input_file || !output_file || !filter_name)
    {
        fprintf(stderr, "Usage: %s -i input_file -o output_file -f filter\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Get the filter function
    filter = get_filter_function(filter_name);
    if(!filter)
    {
        fprintf(stderr, "Invalid filter specified. Use 'upper', 'lower', or 'null'.\n");
        exit(EXIT_FAILURE);
    }

    // Open the input file
    input_fd = open(input_file, O_RDONLY | O_CLOEXEC);
    if(input_fd < 0)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Create the output file
    output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC);
    if(output_fd < 0)
    {
        perror("Error creating output file");
        close(input_fd);
        exit(EXIT_FAILURE);
    }

    // Read from input file and write to output file
    while((bytes_read = read(input_fd, &buffer, 1)) > 0)
    {
        char transformed = filter(buffer);
        if(write(output_fd, &transformed, 1) != 1)
        {
            perror("Error writing to output file");
            close(input_fd);
            close(output_fd);
            exit(EXIT_FAILURE);
        }
    }

    if(bytes_read < 0)
    {
        perror("Error reading from input file");
    }

    close(input_fd);
    close(output_fd);

    // Print success message
    printf("File transformed successfully.\n");
    return EXIT_SUCCESS;
}
