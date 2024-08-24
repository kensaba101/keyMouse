# keyMouse
Control your cursor using just your keyboard

## Features

- **Cursor Control**: Move the cursor using WASD keys.
- **Precision Mode**: Enable finer control over cursor movements if necessary.
- **Simple Setup**: Easy to compile and run on any MacOS machine. 

## Requirements

- MacOS
- Command line tools for Xcode (including `clang++` compiler)

## Installation

1. **Clone the Repository**

   ```bash
    git clone https://github.com/kensaba101/keyMouse.git
    cd keyMouse
    ```

2. **Compile the Program**

    ```bash
    clang++ -o ./build/keyMouse -I./include -framework ApplicationServices ./src/main.cpp ./src/keyMouse.cpp
    ```

## Usage

1. **Run the Program**

    ```bash
    ./build/keyMouse
    ```
    
2. **Instructions:**

- Press **FN (Globe)** key to enter mouse mode.
- Use the **WASD** keys as direction keys to move the cursor.
- Precision Mode: Press and hold **shift** while using the WASD keys to move the cursor with greater precision.
- Press **Q** for a left mouse button (LMB) click, and **E** for right mouse button (RMB) click. 

## Contributing

Pull requests are always welcome!