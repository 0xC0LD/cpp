#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>

int main(int argc, char* argv[]){
	
	bool gameOver = false;
	
	int time = 0;
	int health = 100;
	
	while (!gameOver){
		
		std::cout << &time   << "   time: "   << time   << std::endl;
		std::cout << &health << "   health: " << health << std::endl;
		
		time++;
		health = health + 10;
		
		getch();
	}
	
	return 0;
}
