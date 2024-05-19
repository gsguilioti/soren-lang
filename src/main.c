#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* read_file(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) 
    {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) 
    {
        fclose(file);
        free(content);
        exit(EXIT_FAILURE);
    }

    content[file_size] = '\0';

    fclose(file);
    return content;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char filename[100];
    strcpy(filename, ".//example//");
    strcat(filename, argv[1]);
    
    char* content = read_file(filename);
    printf("%s\n", content);

    return 0;
}
