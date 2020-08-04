#include "image.h"
#include "ppm.h"

int main(){
  ppm p = PPM_new("./assets/merida.ppm"); 
  int nb_pixels = PPM_nbPixels(p);
  color *img = malloc(nb_pixels * sizeof(color));
  color *img1 = malloc(PPM_nbPixels(p) * sizeof(color));
  

  //-------------------------------------------------
  img = PPM_pixels(p);
  I_negative(img, nb_pixels);
  PPM_save(p,img,"./assets/newImages/negative.ppm");

  //-------------------------------------------------
  p = PPM_new("./assets/merida.ppm"); 
  img = PPM_pixels(p);
  I_permute (img, nb_pixels);
  PPM_save(p,img,"./assets/newImages/permute.ppm"); 

  //-------------------------------------------------
  p = PPM_new("./assets/merida.ppm"); 
  img = PPM_pixels(p);
  I_grayScale(img, nb_pixels);
  PPM_save(p,img,"./assets/newImages/grayScale.ppm"); 

  //-------------------------------------------------
  p = PPM_new("./assets/merida.ppm"); 
  img = PPM_pixels(p);
  I_compose(img,img1, nb_pixels, C_new(255,255,255));
  PPM_save(p,img,"./assets/newImages/composed.ppm"); 

  // //-------------------------------------------------
  p = PPM_new("./assets/merida.ppm"); 
  img = PPM_pixels(p);
  I_threshold(img, nb_pixels, 100);
  PPM_save(p,img,"./assets/newImages/threshold.ppm"); 

  // //-------------------------------------------------
  p = PPM_new("./assets/merida.ppm"); 
  img = PPM_pixels(p);
  I_gradient(img, img1, nb_pixels);
  PPM_save(p,img1,"./assets/newImages/gradient.ppm"); 

  // //-------------------------------------------------
  p = PPM_new("./assets/merida.ppm"); 
  img = PPM_pixels(p);
  I_motionBlur(img,img1,nb_pixels,25);
  PPM_save(p,img1,"./assets/newImages/motionBlur.ppm"); 


  return 0;
}