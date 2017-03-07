#include "CImg.h"
#include <iostream>
#include <Shellapi.h>
#include <windows.h>

using namespace cimg_library;
using namespace std;

// Declare colors
const unsigned char
      white[]  = { 255, 255, 255 },
	  black[] = { 0, 0, 0 },
	  red[] = { 120, 50, 80 },
      yellow[] = { 200, 155, 0 },
	  green[] = { 30, 200, 70 },
	  purple[] = { 175, 32, 186 },
      blue[] = { 55, 140, 185 },
	  grey[] = { 127, 127, 127 };


// Run a selected effect
//-----------------------
void start_item(const unsigned int menu_number) {
  switch (menu_number) {
  case 1:{
	 	ShellExecute(NULL, "open", "admin.exe", NULL, NULL, SW_SHOWNORMAL);		
  		break;
  		}
  case 2:{
	 	ShellExecute(NULL, "open", "client.exe", NULL, NULL, SW_SHOWNORMAL);	
        break;
   		 }
  case 3:{
		ShellExecute(NULL, "open", "http://projectzee.000webhostapp.com/"
		, NULL, NULL, SW_SHOWNORMAL);
   		break; 
		}
  case 4:{

		CImg<unsigned char> my_picture("about.bmp");
			
		my_picture.draw_text(420,100, "Project Zee is a future restaurant management system " , white, 0,1,40);
		my_picture.draw_text(430,150, "that aims to easen the lives of both the administration ," , white, 0,1,40); 
		my_picture.draw_text(430,200, "and the customer. It is composed of two executable programmes.  ", white, 0,1,40); 
		my_picture.draw_text(430,250,"One for the administrator (store) and one for the client.", white, 0,1,40); 
		my_picture.display("Project Zee");
        break;		
   		 }
		          
  default:
          break;
  }
}

int main(int argc, char **argv) {

  const unsigned int NUM_OF_ITEMS = 4;
  const unsigned int TEXT_HEIGHT = 22;
  

  unsigned int menu_number = cimg_option("-run",0,0);
  
  if (menu_number)
  	start_item(menu_number);
  else {
    cimg::info();

    // Initial height
    int y0 = 2*13;
    
    
  // ------------------------Intro Screen--------------------------
  CImg<unsigned char> image("bg.bmp");
  image.draw_text(50,y0 - 3,"Casimiro, Chan, and Garan presents...",yellow,8,1,35);


  CImgDisplay disp1(image, "Welcome to our Program!");
  disp1.display(image).wait(1900);
  CImgList<unsigned char> colors;

  CImgList<float> particles;
  float time = 0, speed = 100.0f;

  while (!disp1.is_closed() && !disp1.is_keyQ() && !disp1.is_keyESC()) {

    if (disp1.button()&1 || !particles.size() || (--time)<0) {
      particles.insert(CImg<>::vector((float)cimg::rand()*image.width(),(float)image.height(),
                                      (float)cimg::rand(-1,1)*4,-6 - (float)cimg::rand()*3,
                                      30 + 60*(float)cimg::rand(),3));
      colors.insert(CImg<unsigned char>::vector(255,255,255));
      time = (float)(cimg::rand()*speed);
    }
    image*=0.92f;

    cimglist_for(particles,l) {
      bool remove_particle = false;
      float &x = particles(l,0), &y = particles(l,1), &vx = particles(l,2), &vy = particles(l,3),
            &t = particles(l,4), &r = particles(l,5);
      const float r2 = (t>0 || t<-42)?r/3:r*(1 - 2*(-(t + 2)/40.0f)/3);
      image.draw_ellipse((int)x,(int)y,r,r2,(float)(std::atan2(vy,vx)*180/cimg::PI),colors[l].data(),0.6f);
      x+=vx; y+=vy; vy+=0.09f; t--;
      if (y>image.height() + 10 || x<0 || x>=image.width() + 10) remove_particle = true;

      if (t<0 && t>=-1) {
        if ((speed*=0.9f)<10) speed=10.0f;
        const unsigned char
          r = (unsigned char)std::min(50 + 3*(unsigned char)(100*cimg::rand()), 255),
          g = (unsigned char)std::min(50 + 3*(unsigned char)(100*cimg::rand()), 255),
          b = (unsigned char)std::min(50 + 3*(unsigned char)(100*cimg::rand()), 255);
        const float di = 10 + (float)cimg::rand()*60, nr = (float)cimg::rand()*30;
        for (float i=0; i<360; i+=di) {
          const float rad = i*(float)cimg::PI/180, c = (float)std::cos(rad), s = (float)std::sin(rad);
          particles.insert(CImg<>::vector(x,y,2*c + vx/1.5f,2*s + vy/1.5f,-2.0f,nr));
          colors.insert(CImg<unsigned char>::vector(r,g,b));
        }
        remove_particle = true;
      } else if (t<-1) { r*=0.95f; if (r<0.5f) remove_particle=true; }
      if (remove_particle) { particles.remove(l); colors.remove(l); l--; }
    }
    if (disp1.button()&2) cimglist_for(particles,l) if (particles(l,4)>0) particles(l,4)=0.5f;

    disp1.display(image).wait(25);
    if (disp1.is_keyCTRLLEFT() && disp1.is_keyF()) disp1.resize(640,480,false).toggle_fullscreen(false);
    if (disp1.is_resized()) disp1.resize(disp1,false);
    
   	    image.draw_text(50,y0 - 3,"Project Zee",yellow,8,1,40);
		image.draw_text(50,125, "Project Zee is a future restaurant management system " , white, 0,1,30);
		image.draw_text(50,175, "that aims to easen the lives of both the administration ," , white, 0,1,30); 
		image.draw_text(50,225, "and the customer. It is composed of two executable  ", white, 0,1,30); 
		image.draw_text(50,275, " programmes. One for the administrator (store) and", white, 0,1,30); 
		image.draw_text(50,325, " one for the client.", white, 0,1,30);		
		image.draw_text(250,400, "Close this window to continue", blue, 0,1,20);
  }
    
    
    
    // Set-up the text background with title highlight
    CImg<unsigned char> back("bg.bmp");
    back.draw_rectangle(0,y0 - 7,back.width() - 1,y0 + 20,white);
    
    // Set-up the text foreground, text, image;
    CImg<unsigned char> fore, text, img;

	fore.assign(back.width(),50,1,1,0).draw_text(20,y0 - 3,"Project Zee:",grey,0,1,23);
    (fore+=fore.get_dilate(3).dilate(3)).resize(-100,-100,1,3);

    text.draw_text(1,1,
                   "1. Project Zee (for Admins)\n"
                   "2. Project Zee (for Clients)\n"
                   "3. HTML Documentation\n"
                   "4. About Project Zee\n", 
                                                    
                   white,0,1,TEXT_HEIGHT).resize(-100,-100,1,3);
                   
    fore.resize(back,0).draw_image(20,y0 + 3*13,text|=text.get_dilate(3)>>4);

    CImgDisplay disp(back,"Project Zee'",0,false,true);
    disp.move((disp.screen_width() - disp.window_width())/2,(disp.screen_height() - disp.window_height())/2);
    img = back;
	back*=0.15f;
	
    for (y0 += 3*13; !disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC(); menu_number = 0) {
    	
      while (!menu_number && !disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC()) {

	    img*=0.85f; img+=back;

		// Display foreground text
        const unsigned char *ptrs = fore.data();
        cimg_for(img,ptrd,unsigned char) {
			const unsigned char val = *(ptrs++);
			if (val) *ptrd = val;
		}

		// Display highlight
        const int y = (disp.mouse_y() - y0)/TEXT_HEIGHT, _y = TEXT_HEIGHT*y + y0 + 9;
        if (y>=0 && y<NUM_OF_ITEMS) {
          for (int yy = _y - 9; yy <=_y + 9; ++yy)
            img.draw_rectangle(0,yy,0,1,img.width() - 1,yy,0,0,(unsigned char)(150 - 14*cimg::abs(yy - _y)));
        }
        
        // Set button for the click
        if (disp.button()) {
			menu_number = 1 + (disp.mouse_y() - y0)/TEXT_HEIGHT;
			disp.set_button();
		}
		
        disp.resize(disp,false).display(img).wait(25);
      }
      start_item(menu_number);
    }
  }

  std::exit(0);
  return 0;
}
