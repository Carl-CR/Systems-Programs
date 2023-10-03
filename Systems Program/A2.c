#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

//Making the path and sizes
int length = 256;
char currentpath[256] = "";
char startpath[256] = "";

//Getting the time 
time_t Starttime; 

//Making the log file; 
FILE *logfile; 

//Update the path
void updatePath(char additionalpath[], int length){ 
    strncat(currentpath, additionalpath, length);
}

//Set permission for the text file created
void permissions(char path[]){ 
    //Set the file to read only
    char mode[] ="444"; 
    int x; 
    x = strtol(mode, 0, 8); 
    if (chmod(path, x) < 0){ 
        printf("Error in chmod (%s, %s) - %d (%s)\n", path, mode, errno, strerror(errno));
        exit(1);
    }
    //Set permission message for the file
    char msg[length];
    strcpy(msg, "Permission for file at "); 
    strncat(msg,path,80); 
    strncat(msg," to read-only! \n",80);
    printf(msg,path); 

    //Logging data into file
    time(&Starttime);
    fputs(ctime(&Starttime), logfile); 
    //fputs("\n", logfile);
    fputs(msg, logfile);
    fputs("\n", logfile);
}

//Making the text in the profile.txt 
void makeTxt(char name[], char path[]){ 
    //Making the text data
    char data[length]; 
    strcpy(data, name); 
    strncat(data, " profile created on ",length); 
    strncat(data, ctime(&Starttime), 80);

    //Creating the textfile containing the profile data
    FILE *txtfile; 
    txtfile = fopen(path, "w"); 

    if (txtfile == NULL){ 
        printf("unable to create text file.\n");
    }
    else{ 
        fputs(data, txtfile);
    }
    fclose(txtfile);
}

//Resets the path
void resetPath(){ 
    for (int i = 0; i < length; i++){ 
        currentpath[i] = startpath[i];
    }
}

//Making the directory along with the paths
void makeDir(char buffer[]){ 
    int count = 0;
    int init_size = strlen(buffer);
    char remove[] = ",";
    char name[length];
    char *ptr = strtok(buffer, remove); 
    char type[50];

    //While loop checking if the buffer is NULL or the count reaches 4 
    //which is the max amount of directory needed to be created
    while (ptr != NULL && count < 4){
        //For creating the root directories
        if (count < 3){ 
            //Will check whether the path is the user or the root
            updatePath(ptr, length);
            if (count == 0){ 
                strcpy(type, "root");
            }
            if (count == 1){ 
                strcpy(name, ptr);
                strcpy(type, "user");
            }
            if (count < 2){ 
                //Opening and checking the dir
                DIR* dir = opendir(currentpath);
                if (dir) { 
                    printf("Directory already exists\n"); 
                    closedir(dir);
                }
                else if (ENOENT == errno){ 
                    //Creating root directory message
                    char msg[length];
                    strcpy(msg,ptr); 
                    strncat(msg," ",5);
                    strncat(msg,type,80); 
                    strncat(msg," directory created!\n", 80);
                    printf(msg, ptr, type);

                    //Logging data into file
                    time(&Starttime);
                    fputs(ctime(&Starttime), logfile); 
                    //fputs("\n", logfile);
                    fputs(msg, logfile);
                    fputs("\n", logfile);

                    mkdir(currentpath, 0777);
                }
            }
            else { 
                //Opening and checking the dir
                DIR* dir = opendir(currentpath);
                if (dir){ 
                    printf("Directory already exists\n"); 
                    closedir(dir); 
                }
                else if (ENOENT == errno){ 
                    //Creating home directory message
                    char msg[length]; 
                    strcpy(msg,ptr); 
                    strncat(msg, " directory for ",20); 
                    strncat(msg,name,80); 
                    strncat(msg, " created!\n", 80);
                    printf(msg, ptr, type);

                    //Logging data into file
                    time(&Starttime);
                    fputs(ctime(&Starttime), logfile); 
                    //fputs("\n", logfile);
                    fputs(msg, logfile);
                    fputs("\n", logfile);

                    mkdir (currentpath, 0777);
                }
            }
            ptr = strtok(NULL, ","); 
            updatePath("/",1);
        }
        //Creating the profile.txt after making the home and root directories
        else if (count == 3){ 
            updatePath("profile.txt",20); 
            makeTxt(name, currentpath); 
            permissions(currentpath);
        }
        count++;
    }
}


int main(){ 
    //Opening and writing in the log file
    logfile = fopen("logfile.txt","w");

    //Reading the list file containing the data
    char buffer[1024];
    FILE *file = fopen("list.txt", "r"); 
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }    
   
    //Logging data into file
    time(&Starttime);
    fputs(ctime(&Starttime), logfile); 
    //fputs("\n", logfile);
    fputs("Reading data from the text file... \n",logfile); 
    fputs("\n", logfile);
    fputs(ctime(&Starttime), logfile);
    fputs("Done reading data from the text file... \n",logfile);
    fputs("\n", logfile);

    //Make the directory and resets the path after use
    while (fgets(buffer,length, file)){ 
        makeDir(buffer); 
        resetPath();
    }
    return 1;
}