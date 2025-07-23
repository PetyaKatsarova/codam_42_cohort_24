$, $(...) – VARIABLE EXPANSION
$ means "use a variable".
$(...) is how we expand a variable.

$(NAME)     → expands to "cub3d"
$@          → expands to current *target*
$<          → expands to first *prerequisite*
$^          → expands to all *prerequisites*
--------------------------------
SRCS = $(wildcard src/*.c)
Means: “give me all .c files in the src/ folder”.
-------------------------------

:=	Assign variable immediately
$(VAR)	Expand a variable
$@	Target filename
$<	First dependency
$^	All dependencies
$(dir $@)	Directory path of target
@	Hide command output
wildcard	List matching files
patsubst	Pattern substitution
.PHONY	Mark rules as non-file-based
-------------------------------------
ifeq ($(UNAME_S),Linux)
    ...
endif
Means: “If OS is Linux, then use these settings.”
--------------------------------------
What is a "graphical environment"?
It’s the part of Linux that shows windows, buttons, images — like your desktop interface (GNOME, KDE, XFCE).
Without it, you're in text-only mode (like the black terminal).
-------------------------------
What is $DISPLAY?
It’s a special variable that tells programs where to open windows.

Example values:

:0 → screen 0 on your local desktop

localhost:10.0 → remote graphical session (like SSH with X11 forwarding)

If $DISPLAY is empty or wrong, then programs like mlx_init() can’t create a window → crash.
============================
check on which system am:
uname -a
Linux NL-DH8XGY3 5.15.90.1-microsoft-standard-WSL2 #1 SMP Fri Jan 27 02:56:13 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
=================================
Show graphical windows from WSL on your Windows desktop
To do this, install an X server on Windows.
 Steps to Run GUI Apps (like Cub3D) from WSL:
1. Install VcXsrv on Windows
Download → Install → Launch XLaunch

Use default settings:

Multiple windows

Start no client

Disable access control

2. Set $DISPLAY correctly in WSL
In your WSL terminal:

bash
Copy code
echo "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0" >> ~/.bashrc
source ~/.bashrc
Or do it manually every time:

bash
Copy code
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
3. Run your Cub3D
bash
Copy code
./cub3d maps/your_map.cub