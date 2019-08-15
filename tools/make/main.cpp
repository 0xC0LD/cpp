#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){
	
	if (argc == 1) { std::cerr << "USAGE: " << argv[0] << " <name> <ext>" << std::endl; return 1; }
	if (argc == 2) { std::cout << "file type missing..." << std::endl; return 1; }

	std::string fileName = argv[1];
	std::string fileType = argv[2];
	std::string fullName = fileName + "." + fileType;
	
	if (argv[2] == std::string("cpp")){
		if (fullName == "win32.cpp"){
			std::ofstream file(fullName);
		    file << "#include <windows.h>"                                                                                                                                                             << std::endl;
			file << "LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {"                                                                                                << std::endl;
			file << "	switch(Message) {"                                                                                                                                                             << std::endl;
			file << "		case WM_DESTROY: { PostQuitMessage(0); break; }"                                                                                                                           << std::endl;
			file << "		default: { return DefWindowProc(hwnd, Message, wParam, lParam); }"                                                                                                         << std::endl;
			file << "	}"                                                                                                                                                                             << std::endl;
			file << "	return 0;"                                                                                                                                                                     << std::endl;
			file << "}"                                                                                                                                                                                << std::endl;
			file << ""                                                                                                                                                                                 << std::endl;
			file << "int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {"                                                                                << std::endl;
			file << "	WNDCLASSEX wc;"                                                                                                                                                                << std::endl;
			file << "	HWND hwnd;"                                                                                                                                                                    << std::endl;
			file << "	MSG msg;"                                                                                                                                                                      << std::endl;
			file << ""                                                                                                                                                                                 << std::endl;
			file << "	memset(&wc,0,sizeof(wc));"                                                                                                                                                     << std::endl;
			file << "	wc.cbSize		 = sizeof(WNDCLASSEX);"                                                                                                                                        << std::endl;
			file << "	wc.lpfnWndProc	 = WndProc;"                                                                                                                                                   << std::endl;
			file << "	wc.hInstance	 = hInstance;"                                                                                                                                                 << std::endl;
			file << "	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);"                                                                                                                               << std::endl;
			file << ""                                                                                                                                                                                 << std::endl;
			file << "	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);"                                                                                                                                  << std::endl;
			file << "	wc.lpszClassName = \"WindowClass\";"                                                                                                                                           << std::endl;
			file << "	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);"                                                                                                                           << std::endl;
			file << "	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);"                                                                                                                           << std::endl;
			file << ""                                                                                                                                                                                 << std::endl;
			file << "	if(!RegisterClassEx(&wc)) { MessageBox(NULL, \"Window Registration Failed!\",\"Error!\",MB_ICONEXCLAMATION|MB_OK); return 1; }"                                                << std::endl;
			file << "	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, \"WindowClass\", \"Caption\", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);" << std::endl;
			file << ""                                                                                                                                                                                 << std::endl;
			file << "	if(hwnd == NULL) { MessageBox(NULL, \"Window Creation Failed!\",\"Error!\",MB_ICONEXCLAMATION|MB_OK); return 1; }"                                                             << std::endl;
			file << "	while(GetMessage(&msg, NULL, 0, 0) > 0) {"                                                                                                                                     << std::endl;
			file << "		TranslateMessage(&msg);"                                                                                                                                                   << std::endl;
			file << "		DispatchMessage(&msg);"                                                                                                                                                    << std::endl;
			file << "	}"                                                                                                                                                                             << std::endl;
			file << "	return msg.wParam;"                                                                                                                                                            << std::endl;
			file << "}"                                                                                                                                                                                << std::endl;
			file.close();
		}
		else {
			std::ofstream file(fullName);
			file << "#include <iostream>"                           << std::endl;
			file << "int main(int argc, char* argv[]){"             << std::endl;
			file << "	std::cout << \"HELLO WORLD\" << std::endl;" << std::endl;
			file << "	return 0;"                                  << std::endl;
			file << "}"                                             << std::endl;
			file.close();
		}
	}
	else if(argv[2] == std::string("bat")) {
		if (fullName == "compile.bat") {
			std::ofstream file(fullName);
			file << "g++ main.cpp -static-libgcc -static-libstdc++ -o main.exe" << std::endl;
			file.close();
		}
		else {
			std::ofstream file(fullName);
			file << "@echo off" << std::endl;
			file.close();
		}
	}
	else {
		std::ofstream file(fullName);
		file.close();
	}
	
	//READ FILE
	std::string line;
	std::ifstream myfile (fullName);
	if (myfile.is_open()){
		while (getline (myfile,line)){ std::cout << "> " << line << std::endl; }
		myfile.close();
	}
	else {
		std::cerr << "ERROR: Unable to open file" << std::endl; 
	}
	
	std::cout << std::endl << "out: " << fullName << std::endl; //PRINT OUT FILE NAME
	
	return 0;
}