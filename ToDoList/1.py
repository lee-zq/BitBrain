import distinctipy
import numpy as np
colors = distinctipy.get_colors(50)
np.set_printoptions(precision=3,suppress=True)
colors = np.array(colors)
print(repr(colors))
