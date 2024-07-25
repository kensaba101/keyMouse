//
//  keyMouse.cpp
//  keyMouse
//

#include "keyMouse.h"

std::unordered_set<CGKeyCode> pressedKeys;

bool lmbDown = false;
bool rmbDown = false;
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

void clickMouse(CGMouseButton button, bool direction) {
    CGPoint cursor = getCurrentCursorPosition();

    // Create and post mouse down event
    if (direction) {
        std::cout << "Mouse down" << std::endl; //test
        CGEventRef mouseDown = CGEventCreateMouseEvent(
            NULL, button == kCGMouseButtonLeft ? kCGEventLeftMouseDown : kCGEventRightMouseDown,
            cursor, button
        );
        CGEventPost(kCGHIDEventTap, mouseDown);
        CFRelease(mouseDown);
    }

    // Create and post mouse up event
    if (!direction) {
        std::cout << "Mouse up" << std::endl; //test
        CGEventRef mouseUp = CGEventCreateMouseEvent(
            NULL, button == kCGMouseButtonLeft ? kCGEventLeftMouseUp : kCGEventRightMouseUp,
            cursor, button
        );
        CGEventPost(kCGHIDEventTap, mouseUp);
        CFRelease(mouseUp);
    }
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
    CGEventFlags flags = CGEventGetFlags(event);

    if (type == kCGEventKeyDown) {
        pressedKeys.insert(keyCode);
        if (keyCode == kVK_FN) { // Handle Fn key
            fnPressed = !fnPressed;
        }

        // Handle LMB and RMB 
        if (keyCode == kVK_ANSI_Q && fnPressed && !lmbDown) { // 'q' key for LMB
            clickMouse(kCGMouseButtonLeft, true);
            lmbDown = true;
        } else if (keyCode == kVK_ANSI_E && fnPressed && !rmbDown) { // 'e' key for RMB
            clickMouse(kCGMouseButtonRight, true);
            rmbDown = true;
        }


    } else if (type == kCGEventKeyUp) {
        pressedKeys.erase(keyCode);

        // Handle LMB and RMBq
        if (keyCode == kVK_ANSI_Q && fnPressed) { // 'q' key for LMB
            clickMouse(kCGMouseButtonLeft, false);
            lmbDown = false;
        } else if (keyCode == kVK_ANSI_E && fnPressed) { // 'e' key for RMB
            clickMouse(kCGMouseButtonRight, false);
            rmbDown = false;
        }
    }
    
    // Handle Shift key based on event flags
    if (flags & kCGEventFlagMaskShift) {
        pressedKeys.insert(kVK_Shift);
    } else {
        pressedKeys.erase(kVK_Shift);
    }
    
    
    if (fnPressed) updateCursorPosition();
    printPressedKeys();
    return event;
}
