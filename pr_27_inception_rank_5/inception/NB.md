Step-by-step: Add hostname to Windows hosts file

Press Win + R
Type: notepad C:\Windows\System32\drivers\etc\hosts
Click OK
Click "Yes" if admin prompt appears
At the end of the file, add new line:
127.0.0.1 inception.42.fr
Press Ctrl + S (Save)
Close Notepad
Test:
Open browser, go to: https://inception.42.fr