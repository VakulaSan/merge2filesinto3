#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE 250

void deleteLine(FILE *srcFile, FILE *tmpFile, const int line);
void printFile(FILE *fptr);

int main(void)
{
     FILE *srcFile;
     FILE *tmpFile;

     char path[100];

     int line;

     /* Input file path and line number */
     printf("Enter file path: ");
     scanf("%s", path);

     printf("Enter line number to remove: ");
     scanf("%d", &line);

     /* Try to open file */
     srcFile = fopen(path, "r");
     tmpFile = fopen("delete-line.tmp", "w");

     if (srcFile == NULL || tmpFile == NULL)
     {
          printf("Unable to open the file.\n");
          printf("Please check if file exists or you have read/right priveleges.");
          exit(EXIT_FAILURE);
     }

     printf("\nFile contents before removing line.\n");
     printFile(srcFile);

     rewind(srcFile);
     deleteLine(srcFile, tmpFile, line);

     fclose(srcFile);
     fclose(tmpFile);

     remove(path);
     rename("tmpFIle.tmp", path);

     printf("nFile contents after removing %d line.\n", line);
     srcFile = fopen(path, "r");
     printFile(srcFile);
     fclose(srcFile);

     return 0;
}

void printFile(FILE *fptr)
{
     char ch;

     while ((ch = fgetc(fptr)) != EOF)
          putchar(ch);
}

void deleteLine(FILE *srcFile, FILE *tmpFile, const int line)
{
     char buffer[BUFFER_SIZE];
     char count = 1;

     while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
     {
          if (line != count)
          {
               fputs(buffer, tmpFile);
          }
          count++;
     }
}