@echo off
::wait 3 seconds
timeout /t 3
::start spaming "123"
spam.exe "123"

:: after starting the spam use 'q' to quit...
::
:: Since programs can't send special chars/keys like -_=+[{]};:'"\|,<.>/? because "security purposes" (says windows), 
:: I made these special chars/keys do other cool things:
::    / == ENTER
::    < == BACKSPACE
::    + == FIRST MOUSE CLICK
::    ; == ALT + F4
::    } == CTRL + V
::    _ == WIN + D
::    > == WIN + R
::
:: >spam.exe --help
::
:: Author: C0LD
:: USAGE: spam "sleep (ms)" "string to spam"
::   / == VK_RETURN
::   < == VK_BACK
::   + == VK_LBUTTON
::   ; == VK_MENU + VK_F4
::   } == VK_CONTROL + VK_KEY_V
::   _ == VK_LWIN + VK_KEY_D
::   > == VK_LWIN + VK_KEY_R