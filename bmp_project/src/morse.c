#include "morse.h"

//----------------------------------------------------------------------------------------------------

char* morseEncode(char x) { 
  switch (tolower(x)) { 
    case 'a': return ". ---   "; 
    case 'b': return "- . . .   "; 
    case 'c': return "--- . --- .   "; 
    case 'd': return "--- . .   "; 
    case 'e': return ".   "; 
    case 'f': return ". . --- .   "; 
    case 'g': return "--- --- .   "; 
    case 'h': return ". . . .   "; 
    case 'i': return ". .   "; 
    case 'j': return ". --- --- ---   "; 
    case 'k': return "--- . ---   "; 
    case 'l': return ". --- . .   "; 
    case 'm': return "--- ---   "; 
    case 'n': return "--- .   "; 
    case 'o': return "--- --- ---   "; 
    case 'p': return ". --- --- .   "; 
    case 'q': return "--- --- . ---   "; 
    case 'r': return ". --- .   "; 
    case 's': return ". . .   "; 
    case 't': return "---   "; 
    case 'u': return ". . ---   "; 
    case 'v': return ". . . ---   "; 
    case 'w': return ". --- ---   "; 
    case 'x': return "--- . . ---   "; 
    case 'y': return "--- . --- ---   "; 
    case 'z': return "--- --- . .   ";

    case '0': return "--- --- --- --- ---   "; 
    case '1': return ". --- --- --- ---   "; 
    case '2': return ". . --- --- ---   "; 
    case '3': return ". . . --- ---   "; 
    case '4': return ". . . . ---   "; 
    case '5': return ". . . . .   "; 
    case '6': return "--- . . . .   "; 
    case '7': return "--- --- . . .   "; 
    case '8': return "--- --- --- . .   "; 
    case '9': return "--- --- --- --- .   "; 
    case ':': return "--- --- --- . . .   ";
    case ',': return "--- . . --- ---   ";
    case '?': return ". . --- --- . .   ";
    case '-': return "--- . . . . ---   ";
    case '.': return ". --- . --- . ---   ";
    case '!': return "--- . --- . --- ---   ";
    case ' ': return "  ";
    default :  return ". . . . . . . .   ";


  } 
} 

//----------------------------------------------------------------------------------------------------

char *morseConvert(char *str) {
    long int current = strlen(str)*2; //current size of encoded string
    char *currentcode; // encoded string of current character
    int currentpos = 0; // current position in the encoded string
    char *new = (char *) malloc(sizeof(char)*current); //allocation of encoded string
    new[0] = '\0';
    
    for (int i = 0; i < strlen(str); i++) {
        currentcode = morseEncode(str[i]);
        if (strlen(new) + strlen(currentcode) > current) {  //in case of overflow
            if (current * 2 > strlen(new) + strlen(currentcode)) 
                current *= 2;
            else {
                current += strlen(new) + strlen(currentcode);
                current *= 2;
            }
            new = (char *) realloc(new, current); //in case of overflow, it is useful to realloc the string
        }
        new = strcat(new, currentcode); //adding new morse code to the string
        currentpos += strlen(currentcode);
    }
    new[currentpos] = '\0';
    return new;
}

//----------------------------------------------------------------------------------------------------
