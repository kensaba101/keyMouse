//
//  keyMouse.h
//  keyMouse

#ifndef keyMouse_h
#define keyMouse_h

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <unordered_set>

#define kVK_FN 0xb3

// Function to print the contents of the pressedKeys set
void printPressedKeys();

// Function to get the current mouse cursor position
CGPoint getCurrentCursorPosition();

// Function to move the mouse cursor by the specified deltaX and deltaY values
void moveMouse(int deltaX, int deltaY);

// Function to update the cursor position based on pressed keys
void updateCursorPosition();

// Callback function to capture and process key events
CGEventRef keyPressCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon);

#endif /* main_h */
