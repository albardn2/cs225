#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG input_image;
  input_image.readFromFile(inputFile);
  int width = input_image.width();
  int height = input_image.height();
  int count  = 1;
  for (int y = 0; y < height; y++){
    for (int x  = 0; x < width; x++){
      if (count > width*height/2){
          break;
      }
      cs225::HSLAPixel & pixel1  =input_image.getPixel(x,y);
      cs225::HSLAPixel & pixel2 = input_image.getPixel(width-1-x,height-1-y);
      cs225::HSLAPixel temp = input_image.getPixel(x,y);
      pixel1 = pixel2;
      pixel2 = temp;
      count++;
      std::cout << "this is " <<width << "x" << height << " = " << count << std::endl;
    }
  }
  input_image.writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned int y = 0; y < height; y++){
    for (unsigned int x  = 0; x < width; x++){
      cs225::HSLAPixel & pixel1  = png.getPixel(x,y);
      pixel1.s = 0.5;
      pixel1.l = 0.5;
      if (x == y){
        pixel1.h = 333;
      } else if (x > y){
        pixel1.h = x/(y+1);
      } else{
        pixel1.h = y/(x+1);
      }

    }
  }

  return png;
}
