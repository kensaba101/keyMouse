//
//  main.cpp
//  keyMouse
//

#include "keyMouse.h"


int main() {
    // Create an event tap to capture key presses
    CGEventMask eventMask = (1 << kCGEventKeyDown) | (1 << kCGEventKeyUp);
    CFMachPortRef eventTap = CGEventTapCreate(
        kCGSessionEventTap,          // tap
        kCGHeadInsertEventTap,       // place
        kCGEventTapOptionDefault,    // options
        eventMask,                   // events of interest
        keyPressCallback,            // callback
        NULL                         // user info
    );

    if (!eventTap) {
        std::cerr << "Failed to create event tap." << std::endl;
        return 1;
    }

    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);

    // Run the event loop
    CFRunLoopRun();

    // Cleanup (not reached in this example)
    CFRelease(runLoopSource);
    CFRelease(eventTap);

    return 0;
}
