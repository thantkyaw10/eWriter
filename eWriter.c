#include "eWriter.h"


//charnum < 3500
char* openFile(char *fileName, char*str, int charnum)
{
	//Error checking for charnum
	if (charnum > 3500 || charnum < 1){
		return NULL;
	}
	//Opens filename and gets position of last char
	FILE *fileptr = fopen(fileName, "r");
	fseek(fileptr, 0, SEEK_END);
	unsigned long long pos = ftell(fileptr);
	//If position is bigger than 3300 then just read the last 3300 chars into str
	if (pos > charnum){
	    fseek(fileptr, charnum, SEEK_END);
	    fread(str, sizeof(char), charnum, fileptr);
	    str[charnum] = 0;
	}
	//Else read everything uptill position
	else{
	    fseek(fileptr, 0, SEEK_SET);
	    fread(str, sizeof(char), pos, fileptr);
	    str[pos] = 0;
	}
	fclose(fileptr);
	eprint((uint8_t*) str);
	return str;
}

char* getFile(char* filename)
{
    char prompt [60];
    char ans [3];
    //Prompts user for filename until satisfied
    while(1){
    	eprint((uint8_t*) "Open file:  ");
    	fgets(filename, 50, stdin);
    	filename[strlen(filename) - 1] = 0;
    	if (filename[0] == 'l' && filename[1] == 's'){
    		listdoc();
    		continue;
    	}
    	sprintf(prompt, "Open %s? y/n", filename);
    	eprint((uint8_t*) prompt);
    	fgets(ans, 3, stdin);
    	if (ans[0] == 'Y' || ans[0] == 'y'){
    		break;
    	}
    	else{
    		continue;
    	}
    }
    //TODO Implement print doclist
    return filename;
}


void listdoc()
{
	char buffer[1500];
	DIR *d;
    struct dirent *dir;
    d = opendir("/home/pi/Desktop/eWriterv1.12");
    strcpy(buffer, "FILES: ");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strcat(buffer, dir->d_name);
	    strcat(buffer, ".......");
        }
        closedir(d);
    }
    strcat(buffer, "         Press any key to continue....");
    eprint((uint8_t*) buffer);
    fgets(buffer, 5, stdin);
}
