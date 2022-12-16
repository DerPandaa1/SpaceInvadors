# Building Space Invadors

## Requirements

- cmake 3.15+
- a build utility, ideally Unix make
- raylib (optional)
  - If the systems' raylib could not be found, it will be built automatically

## Building

To build Space Invadors, run the following commands:

```sh
cmake build -G "Unix Makefile" -B build
make -C build
```

After this, the game can be run:

```
./build/SpaceInvadors
```
