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
# mouselook speed change testing
for i in {1..50}
do
    xdotool mousemove_relative $i 0
    sleep 0.01
done
for i in {1..50}
do
    xdotool mousemove_relative -- -$i 0
    sleep 0.01
done

# destroy block test
xdotool mousedown 1
sleep 1
xdotool mouseup 1

# walk testing
xdotool keydown w
sleep 0.5
xdotool keyup w
xdotool keydown s
sleep 0.5
xdotool keyup s

sleep 0.5

# place block test
xdotool click 3

sleep 0.5

# jump testing
xdotool keydown space
sleep 0.05 # sleep time is required for game to recognize spacebar and jump
xdotool keyup space

sleep 1

# inventory test
xdotool key e
sleep 1
xdotool key e


