#include <iostream>
#include <windows.h>
#include <windows.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
	//=====================================
	//			PLAY WAV FILES
	//=====================================
	// SND_ASYNC     = play in the background
	// SND_FILENAME  = play then continue code
	// PlaySound(TEXT("boop.mp3"), NULL, SND_FILENAME);
	
	if (argc == 1){
		cout << argv[0] << " <WavSoundFile>" << endl;
		return 0;
	}
	
	string FILE = argv[1];
	
	if (FILE.find(".wav") != std::string::npos) {
		PlaySound(TEXT(argv[1]), NULL, SND_FILENAME);
	}else{
		cout << "Only .wav files supported." << endl;
	}
	
    return 0;
}