# FDF

A code for the 42 school FDF project; finished with 121% score. In short, you have to visualize a 3d map on screen, using the minilibx library.

For more information about the subject, please check the [Subject File](https://cdn.intra.42.fr/pdf/pdf/111763/en.subject.pdf).\
For more information about the library, please check the [Minilibx documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## Download

Clone the repo to your own computer, and run make. It will automatically install the libraries needed.

```bash
git clone https://github.com/MrBakker/FDF.git
cd FDF
make
```

When running at linux, a few external libraries are required for minlibx to work. They can be installed using the following command:
```bash
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

## Usage

Run the ./fdf binary with a map to visualize. A few are provided in the test_maps folder within the project, but any other (valid!) maps will work.

Once the window has been loaded, the following inputs could be used:
- Pressing z, x or y will rotate the map, pressing the right mouse button will reverse the rotation
- Pressing the up and down arrows will transform the horizontal location of the points in 3d space
- Pressing the left and right arrows will transform the spacing in between point along the x and y axis
- Drag the mouse (with left click) to move the map in the screen
- Drag the mouse (with right click) to rotate the map
- Scroll in/out to zoom in/out
- Press r to reset the view