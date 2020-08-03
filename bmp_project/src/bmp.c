#include "bmp.h"

//----------------------------------------------------------------------------------------------------

BMP readBMP(char *fileName) {

    FILE *fp = fopen(fileName, "rb");  //opening file
    BMP img;

    char ch[2];
    fread(ch, 1, 2, fp);// magic identifier 0x4d42
    if (!(ch[0] == 'B' && ch[1] == 'M')) exit(2);//if it is not BMP 

    int size;
    fread(&size, 1, 4, fp);// size of file
    fseek(fp, 4, SEEK_CUR);//reserved1 and reserved2

    int offset;
    fread(&offset, 1, 4, fp);//offset to image data in bytes from beginning of file (54 bytes)
    img.size_of_header = offset;

    fseek(fp, 4, SEEK_CUR);//DIB size of header    
    
    fseek(fp, 0, SEEK_SET);
    img.header = (char*) malloc(img.size_of_header * sizeof(char));
    fread(img.header, offset, 1, fp); 
    
    fseek(fp, 18, SEEK_SET);

    int w;
    fread(&w, 1, 4, fp);//width
    w = abs(w);

    int h;
    fread(&h, 1, 4, fp);//height
    h = abs(h);
 
    fseek(fp, 2, SEEK_CUR);//number of color planes

    short bits_per_pixel;
    fread(&bits_per_pixel, 1, 2, fp);//bits per pixel
    fseek(fp, offset, SEEK_SET);

    //putting data 
    img.w = w;
    img.h = h;
    img.bytes_per_pixel = abs(bits_per_pixel/8);
    img.data = (unsigned char*)malloc(w*h*img.bytes_per_pixel * sizeof(unsigned char));
    int padding = (4-(w*img.bytes_per_pixel)%4)%4 ;

    for (int y = 0; y < h; y++) {
        fread(&img.data[y * w * img.bytes_per_pixel], 1, w * img.bytes_per_pixel, fp);//filling data (pixels) line by line
        fseek(fp, padding, SEEK_CUR);
    }

    fclose(fp);    
    return img;
}


//----------------------------------------------------------------------------------------------------

void changePixel(int x, int y, BMP *img, RGB color) {
    unsigned char* pixel;
    int rowSize = ((img->bytes_per_pixel * 8 * img->w + 31) / 32) * 4;  //finding rowsize
    int currentrow; 
    if (img->h < 0) {
        currentrow = y; // assign currentrow to y offset
    } else if (img->h > 0) {
        currentrow = (img->h) - y - 1; 
    }

    pixel = ((currentrow * rowSize) + (x*img->bytes_per_pixel) + 16 + img->data); //finding the pixel we need to change

    //assigning the color to pixel
    pixel[1] = color.b;
    pixel[2] = color.g;
    pixel[3] = color.r;
}

//----------------------------------------------------------------------------------------------------

void writeBMP(BMP img, char *fileName) {
    
    FILE *fp = fopen(fileName, "w");
    int size = img.size_of_header + img.bytes_per_pixel*img.w*img.h;//new size

    if(fp){// if there is a file, the image will be written to the file
        fwrite(img.header, img.size_of_header, 1, fp );//writing header from image to file
        fseek(fp, 2, SEEK_SET);
        fwrite(&size, 1, 4, fp); //writing size of image to file
        fseek(fp, 18, SEEK_SET);
        fwrite(&img.w, 1, 4, fp);// writing image width to file
        fseek(fp, img.size_of_header, SEEK_SET); // going to the offset where pixels start
        
        //writing data (pixels) into file
        for (int y = 0; y<img.h; y++) {
            fwrite(&img.data[y*img.w *img.bytes_per_pixel], 1, img.w*img.bytes_per_pixel, fp);
        }
        fclose(fp);
    }
    else{ // else the image should be written to terminal (stdout)
        //doesn't write an image
        fwrite(&img.header, img.size_of_header, 1, stdout );
        for (int y = 0; y<img.h; y++) {
           fwrite(&img.data[y*img.w *img.bytes_per_pixel], 1, img.w*img.bytes_per_pixel, stdout);
        }
    }

}

//----------------------------------------------------------------------------------------------------