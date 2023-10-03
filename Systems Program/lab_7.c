#include <stdio.h>
#include <string.h>

void fileToString(char fileName[], char buffer[], int bufferSize){
    FILE *file = fopen(fileName, "r");
    int linenumber = 1; 
    int count = 0; 

    printf("File opened successfully!\n"); 

    while(fgets(buffer, bufferSize, file))
    { 
        if (count == linenumber){ 
            printf("%s", buffer);
            count++;
            fclose(file);
        }
        else{ 
            count++;
        }
    }

}

int countString(const char* buffer){ 
    int count = 0; 
    
    char wordSearch[] = "Canada";

    int stringlen, searchlen; 
    stringlen = strlen(buffer); 
    searchlen = strlen(wordSearch);

    for (int i = 0; i <= stringlen-searchlen; i++){ 
        int found = 1; 
        for (int j = 0; j < searchlen; j++){ 
            if (buffer[i + j] != wordSearch[j]){ 
                found = 0; 
                break;
            }
        }

        if (found == 1){ 
            count++;
        }
    }
    
    return count;
}

int main(){
    char fileName[] = "lab7.txt"; 
    char buffer[1024]; 
    printf("\nReading the Second line from the file...\n"); 
    printf("*******************************************\n"); 
    fileToString(fileName, buffer, 1024); 
    printf("\nNumber of times Canada appeared in the Second line: %d\n\n", countString(buffer)); 
    return 0; 
}