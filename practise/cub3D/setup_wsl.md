sudo apt install x11-apps -y
xeyes

export DISPLAY=:0

make
./cub3d maps/good/library.cub

./cub3d maps/bad/filetype_wrong.buc should print an error and abort.

