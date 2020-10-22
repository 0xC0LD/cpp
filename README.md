# cpp
### windows C/C++ utils

```
argv2stdout    - print out args
binstr2bmp     - draw a binary string in an image with black and white pixels 
clipboard      - print clipboard (ascii text only)
dpc            - change the desktop background picture
exip           - print current public ip
fib            - print fibonacci numbers
gpath          - print a readable %PATH% variable
playwav        - play a wav file
ss/screenshot  - take a screenshot and save it as a bitmap in %CD%
send           - send a file to an IP and port
sudo           - (admin cmd) a command prompt that asks for admin privileges on start
utc/UTCtime    - print Unix epoch time int
writemem       - write an int to a process' memory

dll injection         - dll injection examples
├── dll injector      - simple dll injector
├── console dll       - a dll that attaches a console to the process
├── exit dll          - a dll that calls exit(0);
├── playwav dll       - a dll that plays a wav file
└── stackoverflow dll - a dll that slows down/crashes the application (creates a thread fork bomb)
 
keylogger            - keylogger examples
├── GetAsyncKeyState - a keylogger that calls GetAsyncKeyState func in a loop (slow, CPU hog)
└── input hook       - a keylogger that makes a keyboard input hook callback (fast)

network shell               - network shell examples
├── bdi (backdoor injector) - a program that makes a persistent backdoor on windows
├── shell_remote_bloated    - fully featured remote shell (meterpreter-like)
├── shell_remote_mini       - minimal remote shell
└── shell_reverse_mini      - minimal reverse shell

sendkeys                    - examples on how to simulate mouse/keyboard input
├── hold LMB                - a program that just holds the left mouse button after a countdown
├── sendkey                 - send keyboard input
├── spamkey                 - spam keyboard input after a countdown
└── spamclick
    ├── CONSOLE SideButtons - replace the side mouse buttons with spam clickers for LMB & RMB
    └── GUI F Keys          - spam clicker (GUI)
```
