#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image baseImage;
  baseImage.readFromFile("alma.png");
  Image sticker1;
  Image sticker2;
  Image sticker3;
  sticker1.readFromFile("sticker2.png");
  sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker2.png");

  sticker1.scale(0.1);
  sticker2.scale(0.1);
  sticker3.scale(0.1);


  StickerSheet sheet(baseImage,10);
  sheet.addSticker(sticker1,190,40);
  sheet.addSticker(sticker2,350,40);
  sheet.addSticker(sticker3,400,40);

  Image render = sheet.render();
  //
  render.writeToFile("myImage.png");


  return 0;
}
