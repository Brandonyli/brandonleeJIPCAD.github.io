## A Dive into NOME3: The Non-Orientable Manifold Editor

NOM3 (Non-Orientable Manifold Editor) is an emerging new Computer-Aided-Design tool being developed by [Professor Carlo Sequin](https://people.eecs.berkeley.edu/~sequin/) and a team of undergraduate and graduate researchers at the University of California, Berkeley. It is specifically built to assist in the design of smooth but precise free-form geometries, such as those by artists like [Eva Hild](https://www.evahild.com/ceramics) or [Charles O. Perry](http://www.charlesperry.com/).

The project is built using C++ as the backend, with a proprietary [NOME language](https://github.com/randyfan/NOME3/wiki/NOME3-Language-Reference) used as the medium in which users can build their creations. The main up-to-date GitHub repository for the NOME3 Project, along with compilation and usage instructions, can be found [here](https://github.com/randyfan/NOME3).

## How does NOME3 work?
The NOME proprietary language is built around specifying meshes, groups, and instances. Meshes and groups can be turned into instances, which are then displayed on the UI.

A mesh is any basic generator that is defined within NOME3. These basic generators can be found [here](https://github.com/randyfan/NOME3/wiki/NOME3-Language-Reference), and can be combined in order to create more advanced and geometrically complicated shapes. Basic generators have parameters that further specify their shape and look, which allows for more flexibility in design.

A group is a number of meshes that have been 'grouped' together into a new mesh, that can then be treated as a singular mesh and have operations performed on. This allows for scalability in the design of more complicated shapes.

An instance of either a mesh or a group is created in order to actually bring an object into the scene. Instances of meshes or groups must be created in order for the mesh or group to be displayed. Multiple instances of the same mesh or group can also be created.

Further operations such as point selection, face deletion, line sweeps, subdivision, screen panning and rotation, etc.) can then be performed once the scene is loaded.

An example of the interplay between meshes, groups, and instances can be seen here:
```markdown
point p1 (0 2 1) endpoint
point p2 (1 0 1) endpoint
point p3 (-1 0 1) endpoint

mesh triangle
    face f1 (p1 p2 p3) endface
endmesh

group diamond
	instance t0 triangle endinstance
	instance t1 triangle rotate (0 1 0) (90) translate (-1 0 1) endinstance
	instance t2 triangle rotate (0 0 1) (180) endinstance
	instance t3 triangle rotate (0 0 1) (180) rotate (0 1 0) (90) translate (-1 0 1) endinstance
endgroup

instance d1 diamond scale (25 25 25) translate (0 0 -25) endinstance
```

## My Contributions to the NOME3 Project

### Stress Test: Fractal Design
There are many steps that the NOME3 application goes through in order to generate an image. Upon loading in a file, NOME3 will parse the NOME language files and call the correct generator classes, create and calcualte the position of underlying OpenMesh points and faces, update with user-specified settings, and then draw them into the scene. This is very resource-intensive, and as such NOME3 is prone to crashes.

My first task was to build a stress test model in order to test the capabilities of the rendering packages that NOME3 uses. My design was 3 recursive repetitions of 3-dimensional diamonds made up of triangle instances surrounded by four toruses. This fractal display was built entirely using the NOME proprietary language.
#### The scene
![](hw1MainPic.png)
![](hw1MainSpin.gif) ![](hw1CloseUpSpinning.gif)

#### Fractal Design
![](hw1FractalPic.png) ![](hw1-fractal-view-2.gif)

The NOM file containing the code can be found [here](https://github.com/Brandonyli/brandonyli.github.io/blob/main/hw1.nom).

### Stress Test: Klein Bottle
A Klein Bottle is a 2-dimensional manifold that has a non-orientable surface in 3-dimensions. The Klein Bottle is interesting because the surface has no boundary (like a sphere), and instead the 'spout' of the bottle wraps into itself and creates a tunnel at the bottom of the 'bottle'. This Klein Bottle was built entirely using the NOME proprietary language, with a Python Notebook script generating the NOME language lines.

#### The scene
![](main.png) ![](mainAlt.png)

#### The 'spout' and bottom
![](inside.gif)
The bottom of the bottle has black-colored faces, which is pecularity of the OpenMesh software in NOME3. Fear not, it is one continuous surface.
![](bottlebottom.png)

The NOM file containing the code can be found [here](https://github.com/Brandonyli/brandonyli.github.io/blob/main/kleinbottle.nom), with accompanying [.ipynb file](https://github.com/Brandonyli/brandonyli.github.io/blob/main/NOME%20File%20Generator%20Example.ipynb).


### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).
