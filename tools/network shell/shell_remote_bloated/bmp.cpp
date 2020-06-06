#include <ole2.h>
#include <olectl.h>
#include <cassert>

PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp){ 
	
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD cClrBits; 
	
    // Retrieve the bitmap color format, width, and height.  
    assert(GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)); 
	
    // Convert the color format to a count of bits.  
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if      (cClrBits == 1)  { cClrBits = 1;  }
	else if (cClrBits <= 4)  { cClrBits = 4;  }
	else if (cClrBits <= 8)  { cClrBits = 8;  }
	else if (cClrBits <= 16) { cClrBits = 16; }
    else if (cClrBits <= 24) { cClrBits = 24; }
    else                     { cClrBits = 32; }
	
    // Allocate memory for the BITMAPINFO structure. (This structure  
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
    // data structures.)  
	
    if (cClrBits < 24){
		
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
		
	}else{
		
		// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));
	}
	
    // Initialize the fields in the BITMAPINFO structure.
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24){ pbmi->bmiHeader.biClrUsed = (1 << cClrBits); }
	
    // If the bitmap is not compressed, set the BI_RGB flag.  
    pbmi->bmiHeader.biCompression = BI_RGB; 
	
    // Compute the number of bytes in the array of color  
    // indices and store the result in biSizeImage.  
    // The width must be DWORD aligned unless the bitmap is RLE 
    // compressed. 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight; 
	
    // Set biClrImportant to 0, indicating that all of the  
    // device colors are important.  
    pbmi->bmiHeader.biClrImportant = 0; 
	
    return pbmi; 
}

void CreateBMPFile(LPCTSTR pszFile, HBITMAP hBMP){ 
	
    HANDLE hf;                  // file handle  
    BITMAPFILEHEADER hdr;       // bitmap file-header  
    PBITMAPINFOHEADER pbih;     // bitmap info-header  
    LPBYTE lpBits;              // memory pointer  
    //DWORD dwTotal;              // total count of bytes  
    DWORD cb;                   // incremental count of bytes  
    BYTE *hp;                   // byte pointer  
    DWORD dwTmp;     
    PBITMAPINFO pbi;
    HDC hDC;
	
    hDC = CreateCompatibleDC(GetWindowDC(GetDesktopWindow()));
    SelectObject(hDC, hBMP);
	
    pbi = CreateBitmapInfoStruct(hBMP);
	
    pbih = (PBITMAPINFOHEADER) pbi; 
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	
    assert(lpBits);
	
    // Retrieve the color table (RGBQUAD array) and the bits  
    // (array of palette indices) from the DIB.  
    assert(GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS));
	
    // Create the .BMP file.  
    hf = CreateFileA(pszFile, GENERIC_READ | GENERIC_WRITE, (DWORD) 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
    assert(hf != INVALID_HANDLE_VALUE);
	
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
    // Compute the size of the entire file.  
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
	
    // Compute the offset to the array of color indices.  
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD); 
	
    // Copy the BITMAPFILEHEADER into the .BMP file.  
    assert(WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp, NULL)); 
	
    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
    assert(WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, ( NULL)));
	
    // Copy the array of color indices into the .BMP file.  
    /*dwTotal = */cb = pbih->biSizeImage; 
    hp = lpBits; 
    assert(WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp, NULL)); 
	
    // Close the .BMP file.  
    assert(CloseHandle(hf)); 
	
    // Free memory.  
    GlobalFree((HGLOBAL)lpBits);
}

HBITMAP screenshot() {
	
	// get the device context of the screen
	HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);     
	// and a device context to put it in
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	
	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);
	
	// maybe worth checking these are positive values
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	
	// get a new bitmap
	HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemoryDC, hBitmap);
	
	//BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, x, y, SRCCOPY);
	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP) SelectObject(hMemoryDC, hOldBitmap);
	
	// clean up
	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);
	
	return hBitmap;
}