#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void mouseX(const double value)
{
    char command[100];
    int speed = (int)(value*100);
    snprintf("xdotool mousemove_relative %d 0", 100, speed);
    system(command);
}

void mouseY(const double value)
{
    char command[100];
    int speed = (int)(value*100);
    snprintf("xdotool mousemove_relative 0 %d", 100, speed);
    system(command);
}

void wsMove(const double value)
{
    if(value > 0.5)
        system("xdotool keyup s keydown w");
    else if(value < -0.5)
        system("xdotool keyup w keydown s");
    else
        system("xdotool keyup w keyup s");
}

void adMove(const double value)
{
    if(value > 0.5)
        system("xdotool keyup a keydown d");
    else if(value < -0.5)
        system("xdotool keyup d keydown a");
    else
        system("xdotool keyup d keyup a");
}

int main() {
    // get minecraft
    system("xdotool search --name \"Minecraft 1.18.2\" windowactivate");
    // unpause the game
    system("xdotool key Escape");

    ClientHandle handle = InitializeLibrary();

    SetName(handle, "Minecraft Demo");

    RegisterAxis(handle, "mouseX", -1.0, 1.0, "Mouse Look", "x", mouseX);
    RegisterAxis(handle, "mouseY", -1.0, 1.0, "Mouse Look", "z", mouseY);

    RegisterAxis(handle, "strafing", -1.0, 1.0, "Movement", "x", wsMove);
    RegisterAxis(handle, "forwardback", -1.0, 1.0, "Movement", "z", adMove);

    ConnectToServer(handle, "192.168.1.7", 45575);

    while(true) {
        LibraryUpdate(handle);
    }

    ShutdownLibrary(handle);
}
