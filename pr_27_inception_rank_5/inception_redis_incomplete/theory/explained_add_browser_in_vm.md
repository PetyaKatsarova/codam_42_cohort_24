sudo apt update

<!-- Install a lightweight desktop environment (XFCE): -->
sudo apt install xfce4 xfce4-goodies

<!--Install a display manager (lightdm):-->
sudo apt install lightdm

sudo apt install chromium

sudo reboot

Log in via the graphical interface and launch Chromium from the



sudo apt remove --purge xfce4 xfce4-goodies lightdm
sudo apt autoremove
-------------------------------------
alternative (minimal setup, no desktop environment):


Xorg is the display server that provides the graphical environment for Linux systems. It’s required to run graphical applications like browsers.

<!--Install Xorg and Chromium:-->
sudo apt install xorg chromium

<!--Start Chromium in a bare X session:-->
startx /usr/bin/chromium

// close chromium:
Press Ctrl+Q or Ctrl+W inside Chromium to close the browser window.
Alternatively, click the close (X) button in the Chromium window.
If you want to exit the X session completely, press Ctrl+Alt+Backspace (this will kill the X server and return you to the terminal).
