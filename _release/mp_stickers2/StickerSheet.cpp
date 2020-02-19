

#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"



StickerSheet::StickerSheet(const Image & picture,unsigned max){
  base_ = picture;
  max_ = max;
  count_ = 0;
  stickerArray_ = new Image*[max];
  x_location = new int[max];
  y_location = new int[max];


}


StickerSheet::~StickerSheet(){
  StickerSheet::_delete();
}

StickerSheet::StickerSheet(const StickerSheet & other)
: base_(other.base_),count_(other.count_),max_(other.max_)
{

stickerArray_ = new Image*[other.max_];
x_location = new int[other.max_];
y_location = new int[other.max_];
for (unsigned int i = 0; i < other.count_; i++ ){
  stickerArray_[i] = new Image(*other.stickerArray_[i]);
  x_location[i] = other.x_location[i];
  y_location[i] = other.y_location[i];
}



}


int StickerSheet::addSticker(Image & sticker,unsigned x,unsigned y){
  if (count_ == max_){
    return -1;
  }
  stickerArray_[count_] = new Image(sticker);
  x_location[count_] = x;
  y_location[count_] = y;
  int index = count_;
  count_++;
  return index;
}


void StickerSheet::changeMaxStickers(unsigned max){
  if (max == max_){

  } else if(max < max_){
      Image ** tempArray = new Image*[max];
      for (unsigned int i = 0; (i < max && i < count_); i++ ){
        tempArray[i] = stickerArray_[i];
    }

    if (count_ > max){
      StickerSheet::_deleteStickerImages(max);
      count_ = max;
    }

    max_ = max;
    delete[] stickerArray_;
    stickerArray_ = tempArray;

  } else {

    Image ** tempArray = new Image*[max];
    for (unsigned int i = 0; (i < max && i < count_); i++ ){
      tempArray[i] = stickerArray_[i];
    }
    max_ = max;
    delete[] stickerArray_;
    stickerArray_ = tempArray;
  }

  int * x_temp = new int[max];
  int * y_temp = new int[max];
  for (unsigned int i = 0;  i < count_ ; i++ ){
    x_temp[i] = x_location[i];
    y_temp[i] = y_location[i];
  }

  delete[] x_location;
  delete[] y_location;

  x_location = x_temp;
  y_location = y_temp;
}


Image * StickerSheet::getSticker(unsigned index){

  if (index >= max_ || index >= count_){
    return NULL;
  }

  Image * ptr = stickerArray_[index];
  return ptr;


}


const StickerSheet & StickerSheet::operator=(const StickerSheet & other){

  if (this == &other){
    return *this;
  } else{
    StickerSheet::_delete();
    StickerSheet::_copy(other);
    return *this;
  }
}


void StickerSheet::removeSticker(unsigned index){

  delete stickerArray_[index];

  unsigned int iter = index + 1;
  while(iter < count_){
    stickerArray_[iter - 1] = stickerArray_[iter];
    x_location[iter - 1] = x_location[iter];
    y_location[iter-1] = y_location[iter];
    iter++;
  }

  stickerArray_[iter] = NULL;
  x_location[iter] = 0;
  y_location[iter] = 0;

  count_ -= 1;
}




Image StickerSheet::render(	)	const {
  Image basePicture = base_;

  for (unsigned int i = 0; i < count_ ; i++){
    Image sticker = *stickerArray_[i];
    unsigned x_coordinate = x_location[i];
    unsigned y_coordinate = y_location[i];
    unsigned int ResizeWidth = x_coordinate + sticker.width();
    unsigned int ResizeHeight = y_coordinate + sticker.height();
    if (ResizeWidth > basePicture.width() || ResizeHeight > basePicture.height())
      basePicture.resize(ResizeWidth,ResizeHeight);

    for (unsigned x = 0 ; x < sticker.width(); x++){
      for (unsigned y = 0; y < sticker.height(); y++){
        cs225::HSLAPixel & pixel = sticker.getPixel(x,y);

        if (pixel.a !=0) {
          cs225::HSLAPixel & basePixel = basePicture.getPixel(x_coordinate + x,y_coordinate + y);
          basePixel = pixel;
        }

      }
    }
  }

  return basePicture;
}

bool StickerSheet::translate	(unsigned index,unsigned x,unsigned y){

  if (index >= count_){
    return false;
  } else{
    x_location[index] = x;
    y_location[index] = y;
    return true;
  }

}




void StickerSheet::_deleteStickerImages(){
  for (unsigned int i = 0; i < count_; i++){
    delete stickerArray_[i];
  }
}


void StickerSheet::_deleteStickerImages(int start){
  for (unsigned int i = start; (i < max_ && i < count_); i++){
    delete stickerArray_[i];
  }

}

void StickerSheet::_delete(){
  for (unsigned int i = 0; i < count_; i++){
    delete stickerArray_[i];
  }
  delete[] stickerArray_;
  delete[] x_location;
  delete[] y_location;

}

void StickerSheet::_copy(const StickerSheet & 	other	){
  base_ = other.base_;
  count_ = other.count_;
  max_ = other.max_;


  stickerArray_ = new Image*[other.max_];
  x_location = new int[other.max_];
  y_location = new int[other.max_];
  for (unsigned int i = 0; i < other.count_; i++ ){
    stickerArray_[i] = new Image(*other.stickerArray_[i]);
    x_location[i] = other.x_location[i];
    y_location[i] = other.y_location[i];
  }





}
