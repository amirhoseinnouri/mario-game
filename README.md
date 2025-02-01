# Mario Game

This is a simple Mario game written in the C programming language. The game features basic platformer mechanics and allows the player to control Mario through different levels while avoiding obstacles and enemies.

## Features

- Classic Mario-style platformer gameplay
- Simple graphics using ASCII or SDL (depending on implementation)
- Keyboard controls for movement and jumping
- Basic collision detection
- Enemy AI (optional)
- Multiple levels

## Installation

To compile and run the game, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/amirhoseinnouri/mario-game.git
   cd mario-game
   ```
2. Compile the game using GCC:
   ```sh
   gcc test.c -o test -lncurses 
   ```
3. Run the game:
   ```sh
   ./test
   ```

## Controls

- **Left Arrow (←):** Move left
- **Right Arrow (→):** Move right
- **Spacebar:** Jump
- **Esc:** Quit the game

## Dependencies

Ensure you have the following libraries installed before compiling:

- SDL2
- SDL2_ttf
- SDL2_image

You can install them using:
```sh
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev   # Debian-based systems
brew install sdl2 sdl2_ttf sdl2_image                                # macOS (Homebrew)
```

## Contributing

Feel free to fork this repository and submit pull requests with improvements, bug fixes, or new features!

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Author

- **Your Name** - [GitHub Profile](https://github.com/amirhoseinnouri)

