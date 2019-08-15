#include <iostream>
#include <windows.h>
#include <cassert>
#include <gdiplus.h>
#include <windows.h>
#include <stdio.h>
#include <ctime>

int main(int argc, char* argv[]) {
	
	if (argc < 3) {
		std::cout << "USAGE: " << argv[0] << " <width> <height> <binary string (e.g. 1111000111010111)>" << std::endl;
		return 1;
	}
	
	int w = atoi(argv[1]);
    int h = atoi(argv[2]);
	
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*w*h;
	
    if(img) { free(img); }
            
    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,sizeof(img));
    int x = 0;
    int y = 0;
    int r = 0;
    int g = 0;
    int b = 0;
	
	std::string str = argv[3];
	int count = 0;
	
	for(int j = h - 1; j >= 0; j--) {
		for(int i = 0; i < w; i++) {
			
			if (count <= (str.length() - 1)) {
				
				switch(str[count]) {
					case '1': default: r=g=b=0; break;
					case '0': r=g=b=255; break;
				}
				std::cout << str[count];
				count++;
			}
			else {
				r=g=b=255;
				std::cout << 0;
			}
			
			x = i; y = (h - 1) - j;
			img[(x+y*w)*3+2] = (unsigned char)(r);
			img[(x+y*w)*3+1] = (unsigned char)(g);
			img[(x+y*w)*3+0] = (unsigned char)(b);
		}
		
		std::cout << std::endl;
	}

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(w    );
    bmpinfoheader[ 5] = (unsigned char)(w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(w>>16);
    bmpinfoheader[ 7] = (unsigned char)(w>>24);
    bmpinfoheader[ 8] = (unsigned char)(h    );
    bmpinfoheader[ 9] = (unsigned char)(h>> 8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for(int i = 0; i < h; i++) {
		
            fwrite(img+(w*(h-i-1)*3),3,w,f);
            fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
	
    fclose(f);
	
	return 0;
}
