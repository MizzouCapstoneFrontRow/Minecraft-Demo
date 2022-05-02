# following these examples
# https://linuxhint.com/xdotool_stimulate_mouse_clicks_and_keystrokes/
# http://manpages.ubuntu.com/manpages/trusty/man1/xdotool.1.html
# https://www.xmodulo.com/simulate-key-press-mouse-movement-linux.html

# need to have minecraft version number to help narrow down windows
xdotool search --name "Minecraft 1.18.2" windowactivate
# unpause the game
xdotool key Escape
# give game time to unpause
sleep 1
# scroll
xdotool click 4

sleep 0.5
xdotool click 4

sleep 0.5
xdotool click 5
sleep 0.5
xdotool click 5
