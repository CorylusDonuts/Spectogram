### Test-SDL but completely changed to use OpenGL

#### For the Mandelbrot renderer:
  - Control             : Arrow keys
  - Zoom out / in       : Z, X
  - Increase iterations : +
  - Decrease iterations : -
  - Inner banding shift : G, V    (Increase/decrease number of bands inside the fractal, also shift the colors to right/left)
  - Overall shift       : F, C    (Can emphasize or decrease the outer banding, also shift the whole color)
  - Color shift r g b + : H, J, K (shift specific color in or out, combine each color band to create new color)
  - Color shift r g b - : B, N, M (shift specific color in or out, combine each color band to create new color)
  
#### What has been done:
  - Implement OpenGL
  - Create OpenGL based fractal viewer
  - 1D DFT in compute shader
  
#### Next to do:
  - Implement audio component for spectogram
  - Create spectrogram
  - Implement UI elements
  - Do cool signal processing stuff
