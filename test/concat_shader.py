import os

library_location = "../library/"
shaders = ["../viewer/shader/procedural.frag", library_location + "util.frag"]
for name in os.listdir(library_location):
    path = library_location + name
    if path not in shaders:
        shaders.append(path)

with open("full.frag", "w") as full:
    for path in shaders:
        with open(path, "r") as shader:
            full.write(shader.read())

with open("full.vert", "w") as full:
    with open("../viewer/shader/screenalignedquad.vert", "r") as shader:
        full.write(shader.read())
