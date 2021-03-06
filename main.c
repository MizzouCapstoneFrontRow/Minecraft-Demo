#include <stdio.h>
#include <stdlib.h>
#include "client.h"

#define DEADZONE 0.4

void mouseX(const double value)
{
    char command[100];
    int speed = (int)(value*100);
    snprintf(command, 100, "xdotool mousemove_relative -- %d 0", speed);
    system(command);
}

void mouseY(const double value)
{
    char command[100];
    int speed = (int)(-value*100);
    snprintf(command, 100, "xdotool mousemove_relative -- 0 %d", speed);
    system(command);
}

void wsMove(const double value)
{
    if(value > DEADZONE)
        system("xdotool keyup s keydown w");
    else if(value < -DEADZONE)
        system("xdotool keyup w keydown s");
    else
        system("xdotool keyup w keyup s");
}

void adMove(const double value)
{
    if(value > DEADZONE)
        system("xdotool keyup a keydown d");
    else if(value < -DEADZONE)
        system("xdotool keyup d keydown a");
    else
        system("xdotool keyup d keyup a");
}

void mouseButtons(const double value)
{
    if(value > DEADZONE)
        system("xdotool mouseup 1 mousedown 3");
    else if(value < -DEADZONE)
        system("xdotool mouseup 3 mousedown 1");
    else
        system("xdotool mouseup 1 mouseup 3");
}

int inv = 0;

void inventory(const double value)
{
    if(value > DEADZONE || value < -DEADZONE)
    {
	    if(inv == 0)
		{
		    system("xdotool key e");
		    inv = 1;
	}
}
    else
    {
	if(inv == 1)
		{
        system("xdotool key e");
	inv = 0;}}
}

void switch_item(const double value)
{
    if(value > DEADZONE)
        system("xdotool click 5");
    if(value < -DEADZONE)
        system("xdotool click 4");
}

void error(enum ErrorCode code, const char *msg) {
    fprintf(stderr, "error (%d): %s\n", code, msg);
}

int main() {
    enum ErrorCode result = NoError;

    // get minecraft
    system("xdotool search --name \"Minecraft 1.18.2\" windowactivate");
    // unpause the game
    system("xdotool key Escape");

    ClientHandle handle = InitializeLibrary();

    result = SetName(handle, "Minecraft Demo");
    if (result != NoError) error(result, "SetName");

    result = RegisterAxis(handle, "mouseX", -1.0, 1.0, "Mouse Look", "x", mouseX);
    if (result != NoError) error(result, "RegisterAxis");
    result = RegisterAxis(handle, "mouseY", -1.0, 1.0, "Mouse Look", "z", mouseY);
    if (result != NoError) error(result, "RegisterAxis");

    result = RegisterAxis(handle, "mouseButtons", -1.0, 1.0, "Mouse Buttons", "x", mouseButtons);
    if (result != NoError) error(result, "RegisterAxis");

    result = RegisterAxis(handle, "inventory", -1.0, 1.0, "Inventory", "z", inventory);
    if (result != NoError) error(result, "RegisterAxis");
    result = RegisterAxis(handle, "itemswitch", -1.0, 1.0, "Switch Item", "z", switch_item);
    if (result != NoError) error(result, "RegisterAxis");

    result = RegisterAxis(handle, "strafing", -1.0, 1.0, "Movement", "x", adMove);
    if (result != NoError) error(result, "RegisterAxis");
    result = RegisterAxis(handle, "forwardback", -1.0, 1.0, "Movement", "z", wsMove);
    if (result != NoError) error(result, "RegisterAxis");

    result = RegisterStream(handle, "game view", "mjpeg", 0);
    if (result != NoError) error(result, "RegisterStream");

    result = ConnectToServer(handle, "127.0.0.1", 45575, 45577);
    if (result != NoError) {
        error(result, "ConnectToServer");
        goto end;
    }

    while(1) {
        result = LibraryUpdate(handle);
        if (result != NoError) {
            error(result, "LibraryUpdate");
            break;
        }
    }

    end:
    ShutdownLibrary(handle);
}
