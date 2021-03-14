#include "IT8951.h"
#include "eWriter.h"


int main (int argc, char *argv[])
{
	if(IT8951_Init())
	{
		fprintf(stderr, "IT8951_Init error \n");
		return 1;
	}

	//Clears screen saver
	IT8951DisplayClear();
	
	//Instantiates 
	char buffer[500];
	char *str = malloc(3500);
	if (!str)
	{
		closeFile();
		return 1;
	}
	
	char *filename = malloc(50);
	if (!filename)
	{
		free(str);
		closeFile();
		return 1;
	}
	
	filename = getFile(filename);

	//Creates new file pointer pgdown
	FILE * fileptr = fopen(filename, "a");
	
	//Instantiate str with openFile
	str = openFile(filename, str, 1000);

	while (fgets(buffer, 500, stdin)){
		//When = input exit program
		if (buffer[0] == '='){
			break;
		}

		//When # is the first char open new file
		if (buffer[0] == 48&& buffer [1] == 48){
			filename = getFile();
			str = openFile(filename, str, 1000);
			fileptr = fopen(filename, "a");
			continue;
		}
		
		//When 1 is pressed scroll up
		if (buffer[0] == 33){
			str = openFile(filename, str, 2500);
		}

		//Getting rid of the new line character gotten at command line and adding \0
		buffer[strlen(buffer) - 1] =  0;

		//Scrolling function
		if (strlen(buffer) + strlen(str) > 3500){
			str = openFile(filename, str, 1000);
		}

		//Adds buffer to document
		fprintf(fileptr, "%s", buffer);

		//Adds buffer to str[]
		strcat(str,buffer);

		//prints str out onto screen
		eprint((uint8_t*) str);
	}
	
	free(str);
	free(filename);
	fclose(fileptr);
	IT8951DisplayClear();
	IT8951_BMP_Example(0, 0, "essvr.bmp");
	IT8951_Cancel();


	return 0;
}
