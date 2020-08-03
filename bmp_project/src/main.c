#include "morse.h"
#include "color.h"
#include "bmp.h"

//------------------------------------------------------------------------------------------

char *substr(char *string, int position, int length){
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
   
   if (pointer == NULL){
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0 ; c < length ; c++){
      *(pointer+c) = *(string+position-1);      
      string++;  
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}

//------------------------------------------------------------------------------------------

char* secondpart(char* str) { 
    int i; 
    char* string = str;
   
    for (i = 0; i < strlen(string); i++) { 
        if (string[i] == ','){ 
            break; 
        }
    } 

  
 
    if (i < strlen(string) - 1) 
        string = substr(string, i + 2, strlen(string) - (i + 1)); 
    else
        return ""; 
    return string;
} 

//-----------------------------------------------------------------------------------------

char* firstpart(char* str) {
    char* string = str;
    int i; 
   
 
    for (i = 0; i < strlen(string); i++) { 
        if (string[i] == ','){ 
            break; 
        }
    } 
  
  
    if (i < strlen(string) - 1) 
        string = substr(string, 1, i); 
  

    else
        return ""; 
    return string;
    
}


//----------------------------------------------------------------------------------------------------

void displayHelp(){
        printf("Syntax:\n");
        printf("./wm [Filename] -text [\"Your text\"] -date -color [the color you want] -pos [y position][x position] -o [newfilename]\n");
}

//----------------------------------------------------------------------------------------------------

void write(char* filename, char* text, RGB color, int x_position, int y_position, char* newfilename) {
    BMP img = readBMP(filename); //reads file to an BMP image
    
    if (text) { // if there was written text in the terminal argument

        if ((img.w - x_position)*(img.h - y_position) < strlen(text) - 4) {  // if there is enough place to write morse code
            printf("Not enough space in the picture\n"); 
            return;
        }

        int i;
        for (i = 0; i < strlen(text); i++) {//the string (morse code) is composed of ., -, and space
            if (text[i] == '.')// if there is dot we will change the pixel
                changePixel(x_position, y_position, &img, color);
            if(text[i] == '-')// if there is - we will change the pixel
                changePixel(x_position, y_position, &img, color);
            x_position++;
            if (x_position == img.w) {// if we reached the end of row
                x_position = 0; // next row will begin from 0 offset
                y_position++;//incrementing y-offset
            }
        }
    }
    writeBMP(img, newfilename); // finally writing image into file
}

//----------------------------------------------------------------------------------------------------

int isnumber(char const *str) { //if the string composed of a number it returns 1, else 0
    for (int i = 0;i < strlen(str);i++) 
        if (!isdigit(str[i])) 
            return 0;
    return 1;
}

//----------------------------------------------------------------------------------------------------

int isBMP(char const *name){ //if the filename ends with ".bmp", then it is bmp file, then function returns 0 
    char* dot = strrchr(name, '.');
    if (!dot || strcmp(dot, ".bmp")) 
        return 0;
    return 1;
}

//----------------------------------------------------------------------------------------------------

int main(int argc, char const *argv[]) {
    char *filename; //initial file to be changed
    char *text = '\0'; // string to be encoded
    char *newfilename = '\0'; //file to which will be written image at the end
    int hasdate = 0, x = 0, y = 0; // hasdate initially is 0, and if there will be -date in the terminal, it will change to 1
    RGB color = newColor(); // initial color -> black
    char* position = '\0';

    if (argc < 2) {//there cannot be less than 2 arguments
        printf("The original file must be provided\n");
        displayHelp();
        return 1;
    }
    
    if (!isBMP(argv[1])) { // initial file should be of extention bmp
        printf("The original file must be bmp file\n");
        displayHelp();
        return 1;
    } else {
        filename = (char *) argv[1];

        if (!filename) { //if there is no initial file the program will stop
            return 1;
        }
    }

    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-text")) {
            if (i+1 >= argc) {
                displayHelp();
                return 1;
            }
            text = (char *) malloc(sizeof(char)*(strlen(argv[i+1])+257));
            strcpy(text, (char *) argv[i+1]);
            i++;
        } else if (!strcmp(argv[i], "-date")) {
            hasdate = 1;// changing value of hasdate
        } else if (!strcmp(argv[i], "-color")) {
            if (i+1 >= argc) {
                displayHelp();
                return 1;
            }
            if (strlen(argv[i+1]) % 2 != 0 || strlen(argv[i+1]) > 6) { //color cannot be more than 6 digits
                printf("Incorrect color\n");
                displayHelp();
                return 1;
            }
            color = getColor(color,argv[i+1]);//setting color taken from string to color object 
            i++;
        } else if (!strcmp(argv[i], "-pos")) {
            char* dot = strrchr((char*)argv[i+1], ',');
            if(i+1 >= argc && !dot){
                displayHelp();
                return 1;
            }else{
                position = (char*)argv[i+1];
                if(strcmp(firstpart(position), "") == 0 || strcmp(secondpart(position), "") == 0){
                    displayHelp();
                    return 1;
                }
                x = atoi(firstpart(position));
                y = atoi(secondpart(position));
                i++;
            }
        } else if (!strcmp(argv[i], "-o")) {
            if (i+1 >= argc) {
                displayHelp();
                return 1;
            }
            if (!isBMP(argv[i+1])) {
                printf("The output file must be bmp file \n");
                displayHelp();
                return 1;
            }
            newfilename = (char *) malloc(100*sizeof(char));
            strcpy(newfilename, (char *) argv[i+1]);
            i++;
        } else {
            printf("Invalid variables given\n");
            displayHelp();
            return 1;
        }
    }

    // if we have date, then add it to the text and turn it to morse code
    if (hasdate) {
        char *date = (char *) malloc(256*sizeof(char));
        time_t tm = time(NULL);
        struct tm *t = localtime(&tm);
        strftime(date, 256, "%a  %d %b %H:%M:%S %Z %Y", t); //getting date string similar to linux -date command
        if (text) { //is there is text we will add date to text
            text = strcat(text, " ");
            text = strcat(text, date);
        } else text = date;//if there is no text we will just assign text to date(because there is date anyway)
    }
    if (text && strcmp(text, ""))   // we have something to write 
        text = morseConvert(text); //convert string to morse

    write(filename, text, color, x, y, newfilename); //writing text to image

    return 0;
}

//----------------------------------------------------------------------------------------------------

