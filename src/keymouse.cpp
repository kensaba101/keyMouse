//
//  keyMouse.cpp
//  keyMouse
//

#include "keyMouse.h"

std::unordered_set<CGKeyCode> pressedKeys;

bool fnPressed = false;

void printPressedKeys() {
    printf("Pressed keys: ");
    for (const auto& key : pressedKeys) {
        printf("%d ", key);
    }
    printf("\n");
}

CGPoint getCurrentCursorPosition() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    return cursor;
}

void moveMouse(int deltaX, int deltaY) {
    // Get the current mouse position
    CGPoint cursor = getCurrentCursorPosition();

    // Create a new mouse move event
    CGEventRef move = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(cursor.x + deltaX, cursor.y + deltaY),
        kCGMouseButtonLeft // ignored
    );

    // Post the event
    CGEventPost(kCGHIDEventTap, move);
    CFRelease(move);
}

void updateCursorPosition() {
    // Check if Shift key is held down
    bool isShiftPressed = pressedKeys.count(kVK_Shift);

    int stepSize = isShiftPressed ? 10 : 100;
    int deltaX = 0, deltaY = 0;

    if (pressedKeys.count(kVK_ANSI_W)) deltaY -= stepSize; // Move up
    if (pressedKeys.count(kVK_ANSI_S)) deltaY += stepSize; // Move down
    if (pressedKeys.count(kVK_ANSI_A)) deltaX -= stepSize; // Move left
    if (pressedKeys.count(kVK_ANSI_D)) deltaX += stepSize; // Move right

    moveMouse(deltaX, deltaY);
}

CGEventRef keyPressCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {
    CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

    if (type == kCGEventKeyDown) {
        pressedKeys.insert(keyCode);
        if (keyCode == kVK_FN) { // Handle Fn key
            fnPressed = !fnPressed;
        }
    } else if (type == kCGEventKeyUp) {
        pressedKeys.erase(keyCode);
    }
    
    // Handle Shift key based on event flags
    CGEventFlags flags = CGEventGetFlags(event);
    if (flags & kCGEventFlagMaskShift) {
        pressedKeys.insert(kVK_Shift);
    } else {
        pressedKeys.erase(kVK_Shift);
    }
    
    
    if (fnPressed) updateCursorPosition();
    printPressedKeys();
    return event;
}
