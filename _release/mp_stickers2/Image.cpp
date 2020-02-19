/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <cmath>

  void Image::lighten(){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l += 0.1;
      if (pixel.l > 1){
        pixel.l = 1;
        }
      }
    }
  }


  void Image::lighten(double amount){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l += amount;
      if (pixel.l > 1){
        pixel.l = 1;
      } else if (pixel.l < 0 ){
        pixel.l  = 0;
      }
      }
    }
  }


  void Image::darken(){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l -= 0.1;
      if (pixel.l < 0){
        pixel.l = 0;
        }
      }
    }
  }


  void Image::Image::darken(double amount){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l -= amount;
      if (pixel.l < 0){
        pixel.l = 0;
      } else if (pixel.l > 1 ){
        pixel.l  = 1;
      }
      }
    }
  }


  void Image::saturate(){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s += 0.1;
      if (pixel.s > 1){
        pixel.s = 1;
        }
      }
    }
  }

  void Image::saturate(double amount){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s += amount;
      if (pixel.s > 1){
        pixel.s = 1;
      } else if (pixel.s < 0 ){
        pixel.s  = 0;
      }
      }
    }
  }


  void Image::desaturate(){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s -= 0.1;
      if (pixel.s < 0){
        pixel.s = 0;
        }
      }
    }
  }


  void Image::desaturate(double amount){
    for (unsigned int x = 0; x < this->width() ; x++){
      for (unsigned int y = 0; y < this->height() ; y++){

      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s -= amount;
      if (pixel.s < 0){
        pixel.s = 0;
      } else if (pixel.s > 1 ){
        pixel.s  = 1;
      }
      }
    }
  }

  void Image::grayscale(){
    for (unsigned int x = 0; x < this->width(); x++) {
      for (unsigned int y = 0; y < this->height(); y++) {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);
        pixel.s = 0;
      }
    }
  }


  void Image::rotateColor(double degrees){

    for (unsigned int x = 0; x < this->width(); x++) {
      for (unsigned int y = 0; y < this->height(); y++) {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);
        double sum = pixel.h + degrees;
        if (sum > 0)
          pixel.h = std::fmod(pixel.h + degrees,360);
        else
          pixel.h = std::fmod(360 + pixel.h + degrees,360);
      }
    }
  }

  void Image::illinify(){
    for (unsigned int x = 0 ; x < this->width() ;x++){
      for (unsigned int y = 0 ;  y < this->height(); y++){

        cs225::HSLAPixel & pixel = this->getPixel(x,y);

        if (std::fabs(216 - pixel.h) > 102.5){
          pixel.h = 11;
        }else{
          pixel.h = 216;
        }
      }
    }
  }

  void Image::scale(double factor){
    unsigned int newWidth  = std::round(this->width() * factor);
    unsigned int newHeight = std::round(this->height() * factor);
    std::cout  << "current width is " << (this->width()) << std::endl;
    std::cout  << "New width is " << newWidth << std::endl;
    std::cout  << "New height is " << newHeight << std::endl;


    cs225::PNG tempImage(newWidth,newHeight);
    float newFactor =  (float)(newWidth)/(float)(this->width());
    std::cout  << "New factor is " << newFactor << std::endl;
    unsigned int x_index = 0;
    unsigned int y_index = 0;
    double x_counter = 0;
    double y_counter = 0;
    int x_floor;
    int y_floor;
    for (unsigned int y = 0; y < this->height(); y++){
      y_counter += newFactor;
      x_counter = 0;
      x_index = 0;
      for (unsigned int x = 0; x < this->width(); x++){
        x_counter += newFactor;
        x_floor = std::floor(x_counter);
        y_floor = std::floor(y_counter);

        if (x_floor > 0 && y_floor > 0 && x_index < newWidth && y_index < newHeight){
          cs225::HSLAPixel target = this->getPixel(x,y);
          for (int i = 0; i < x_floor ; i++ ){
            for  (int j =0 ; j < y_floor; j++){
              if ((x_index + i < newWidth) && (y_index + j < newHeight)){
                cs225::HSLAPixel & pixel = tempImage.getPixel(x_index + i, y_index + j);
                pixel = target;
              }

            }
          }

          x_index +=x_floor;
          x_counter -= x_floor;
        }
      }
      y_index += y_floor;
      y_counter -= y_floor;
    }

    tempImage.writeToFile("xxx.png");


    this->resize(newWidth,newHeight);
    for (unsigned int x =0; x < this->width();x ++){
      for (unsigned int y =0; y < this->height(); y++){
        cs225::HSLAPixel & pixel = this->getPixel(x,y);
        pixel = tempImage.getPixel(x,y);
      }
    }

  }


  void Image::scale(unsigned int w , unsigned int h){
      unsigned int newWidth  = w;
      unsigned int newHeight = h;
      cs225::PNG tempImage(newWidth,newHeight);
      float newFactor =  (float)(newWidth)/(float)(this->width());
      std::cout  << "New factor is " << newFactor << std::endl;
      unsigned int x_index = 0;
      unsigned int y_index = 0;
      double x_counter = 0;
      double y_counter = 0;
      int x_floor;
      int y_floor;
      for (unsigned int y = 0; y < this->height(); y++){
        y_counter += newFactor;
        x_counter = 0;
        x_index = 0;
        for (unsigned int x = 0; x < this->width(); x++){
          x_counter += newFactor;
          x_floor = std::floor(x_counter);
          y_floor = std::floor(y_counter);

          if (x_floor > 0 && y_floor > 0 && x_index < newWidth && y_index < newHeight){
            cs225::HSLAPixel target = this->getPixel(x,y);
            for (int i = 0; i < x_floor ; i++ ){
              for  (int j =0 ; j < y_floor; j++){
                cs225::HSLAPixel & pixel = tempImage.getPixel(x_index + i, y_index + j);
                pixel = target;
              }
            }

            x_index +=x_floor;
            x_counter -= x_floor;
          }
        }
        y_index += y_floor;
        y_counter -= y_floor;
      }

      tempImage.writeToFile("xxx.png");


      this->resize(newWidth,newHeight);
      for (unsigned int x =0; x < this->width();x ++){
        for (unsigned int y =0; y < this->height(); y++){
          cs225::HSLAPixel & pixel = this->getPixel(x,y);
          pixel = tempImage.getPixel(x,y);
        }
      }

    }
