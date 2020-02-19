/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet
{

private:
  Image base_;
  Image ** stickerArray_;
  unsigned count_;
  unsigned max_;

  int * x_location;
  int * y_location;

  void _deleteStickerImages();
  void _delete();
  void _copy(const StickerSheet & 	other	);
  //end not inclusive
  void _deleteStickerImages(int start);


public:

  StickerSheet	(	const Image & 	picture, unsigned 	max );

  ~StickerSheet	();

  StickerSheet	(	const StickerSheet & 	other	);

  int addSticker(	Image & 	sticker,unsigned 	x,unsigned 	y );

  void changeMaxStickers	(	unsigned 	max	);

  Image * getSticker	(	unsigned 	index	);

  const StickerSheet & operator=(	const StickerSheet & 	other	);

  void removeSticker	(	unsigned 	index	);

  Image render()	const ;

  bool translate	(unsigned index,unsigned x,unsigned y);




};
