## OpenGL ES 3.0 Cookbook (examples / source repository)

This repo is a collection of runnable OpenGL ES 3.0 “recipes” organized by chapter, plus a small cross‑platform helper library (`GLPIFramework`). The point is hands-on learning: build a sample, tweak the shader/math/state, and see what changes on screen.

### What you’ll learn overall

- **Core GLES 3.0 pipeline**: buffers/VAOs, vertex + fragment shaders, uniforms, depth/cull state.
- **Lighting and materials**: ambient/diffuse/specular models, per‑vertex vs per‑pixel shading, multiple lights.
- **Textures and FBOs**: 2D/cube maps, compressed textures, render-to-texture, sampling and filtering.
- **Shader techniques**: procedural shaders, stylized effects, discard/alpha tricks.
- **Post-processing**: grayscale, blur, bloom, edge detection, distortion, etc.
- **Scene graphs and interaction**: hierarchy transforms, picking, HUD, cameras, multiple views.
- **Anti-aliasing and shadows**: FXAA/adaptive AA, shadow mapping, VSM/PCF, depth visualization.

---

### `GLPIFramework`

Shared utility/framework code used by many recipes (platform glue, input handling, basic rendering helpers, and common assets). When you see platform subfolders like `Android/` or `iOS/`, they typically contain the app wrapper around the same core recipe logic.

---

### Chapter 1 — Getting started / first app

- **`HelloWorldAndroid` / `HelloWorldiOS`**: the “blue triangle” style first app—creates a context, compiles shaders, draws a primitive, and establishes the render loop.
- **`simpleJNI`**: shows how to bridge Java ↔ native (JNI) to run GLES code from C/C++ on Android.

**You will learn / experiment with:** creating an ES 3.0 context, compiling/linking shaders, basic draw calls, and (for JNI) how the native layer is called and how resources are managed across the boundary.

---

### Chapter 2 — Drawing, transforms, and basic state

- **`OpenGLES3_Primitives`**: drawing common primitive types and understanding vertex assembly.
- **`DrawingAPIs`**: different ways to issue draw calls (arrays vs elements, etc.).
- **`VertexBufferObject`**: moving vertex data into GPU buffers and updating it.
- **`ProjectionSystem`** and **`Move-View-Projection-Analogies`**: camera/projection basics and how MVP matrices affect the result.
- **`DepthTesting`** and **`Culling`**: the “why” behind hidden-surface removal and backface culling.
- **`TouchEvents`**: basic input driving transforms or parameters.
- **`GLPIFrameworkIntro`**: orientation to how the samples are structured.

**You will learn / experiment with:** matrix math, near/far plane effects, winding order and cull modes, depth func, and how changing buffer layouts and draw modes changes performance/visuals.

---

### Chapter 3 — Data organization and modern ES 3.0 features

- **`VertexArrayObject`**: VAOs for binding vertex layout/state once and drawing many times.
- **`UniformBlock`**: uniform buffer objects (UBOs) for grouping parameters and sharing across programs.
- **`Attribute_Layouts`**: explicit attribute locations and consistent vertex formats.
- **`MapBuffer`**: mapping buffers for efficient streaming updates.
- **`Geometric_Instacing`** / **`SimpleGeometricInstancing`**: instanced rendering for many copies of the same mesh.
- **`PrimitiveRestart`**: using primitive restart to reduce index buffer splits.

**You will learn / experiment with:** structuring GPU data for scale (many objects), reducing CPU overhead, and how ES 3.0 features (VAO/UBO/instancing) simplify and speed up your renderer.

---

### Chapter 4 — Model loading

- **`ObjLoader`**: loading and drawing `.obj` meshes.
- **`3DSLoader`**: loading `.3ds` content.
- **`BlenderModels`**: working with exported models/assets.

**You will learn / experiment with:** the asset pipeline (import → vertex/index buffers → draw), coordinate systems, normals/tangents, and what happens when model data is missing or inconsistent.

---

### Chapter 5 — Lighting fundamentals

- **`Ambient`**, **`Diffuse`**, **`Specular`**: individual components of common lighting models.
- **`PhongShader`**, **`PhongDirectionalLight`**, **`PhongPointLight`**: classic Phong lighting in different configurations.
- **`GouraudShader`**: per-vertex lighting and how it differs from per-pixel lighting.
- **`MultipleLights`**: combining multiple light sources.
- **`SpecularHalfWayVectorOptimization`**: using the halfway vector (Blinn-Phong style) optimization.
- **`TwoSideShading`**: shading when you want both sides of geometry to contribute.

**You will learn / experiment with:** light positions/directions, shininess, normal transforms, attenuation, and the visual differences between shading models.

---

### Chapter 6 — Procedural / stylized shaders

- **`SimpleShader`**: baseline shader structure and uniform plumbing.
- **`BrickShader`**, **`GridShader`**, **`Polka3D`**: procedural patterns generated in the fragment shader.
- **`RippleShader`**, **`WobbleShader`**: time-based deformation/animation in shaders.
- **`CircleShader`**, **`RotatingCircleShader`**: analytic shapes and parametric motion.
- **`DebugByColor`**: using color as a debugging tool for shader values.
- **`Discarfragment`**: fragment discard techniques (masks/cutouts).

**You will learn / experiment with:** using UVs and screen-space, animating with time uniforms, debugging shader math, and creating “materials” without textures.

---

### Chapter 7 — Texturing and FBOs

- **`SimpleTexture`**, **`MultipleTexture`**: sampling textures and blending/mixing sources.
- **`CompressedTexture`**: working with compressed formats and understanding tradeoffs.
- **`CubeTexture`**: cube maps for environment effects.
- **`Reflection`** / **`Refraction`**: view-dependent sampling for reflective/refractive looks.
- **`BumpMapping`**: normal perturbation and surface detail.
- **`HeightField`**: height-based terrain or displacement-style rendering.
- **`FBO`**: rendering into textures (render-to-texture) as a building block for post FX.
- **`DiscardingFragmentsWithTex`**: texture-driven masks/alpha cutouts.

**You will learn / experiment with:** sampler state (filter/wrap), mipmaps, coordinate spaces for env mapping, and how FBO attachments/formats impact quality and performance.

---

### Chapter 8 — UI/HUD and localization

- **`FontSimple`**: basic font rendering/text drawing.
- **`HUD`**: overlay UI on top of 3D content.
- **`Localization`**: adapting text/assets for different languages/regions.

**You will learn / experiment with:** mixing 2D and 3D, coordinate systems for UI, and practical app concerns beyond pure rendering.

---

### Chapter 9 — Image filters / post-processing

Recipes such as **`Grayscale`**, **`Gaussian_blur`**, **`Bloom`**, **`EdgeDetection`**, **`Emboss`**, **`CMYK`**, **`CartoonShader`**, **`Twirl`**, **`BarrelDistortion_*`**, etc.

**You will learn / experiment with:** full-screen passes, convolution kernels, multi-pass effects (blur + combine for bloom), sampling offsets, and how “camera effects” are implemented as post-process shaders.

Notes:
- `OpenGL ES 3.0 Cookbook/SourceRepository/Chapter9/Known_Issues.txt` mentions `SphereWithTextureQuad` may intermittently show a blank screen and may need restarting a few times.

---

### Chapter 10 — Scene graph, picking, camera, multi-view

Scene-graph progression samples: **`SG1_withSceneLightMaterial`** through **`SG8_withSG7+MultipleViews`**.

**You will learn / experiment with:** hierarchical transforms, parent/child relationships, different picking strategies (including ray-based picking), HUD button interaction, camera movement, and rendering multiple views of the same scene.

Notes:
- `OpenGL ES 3.0 Cookbook/SourceRepository/Chapter10/Known_Issues.txt` lists some Android picking issues in a few SG recipes.

---

### Chapter 11 — Anti-aliasing and deferred shading

- **`FastApproxAntiAliasing` (FXAA)**: post-process AA.
- **`AdaptiveAntiAliasing`**: adaptive AA approach.
- **`AntiAliasingCircleGeometry`**: geometry/analytic AA example.
- **`DefferedShading`**: a deferred pipeline (G-buffer then lighting pass).

**You will learn / experiment with:** edge detection vs blur tradeoffs in AA, and how deferred shading reorganizes your pipeline (what goes into the G-buffer and why).

Notes:
- `OpenGL ES 3.0 Cookbook/SourceRepository/Chapter11/Known_Issues.txt` indicates these recipes may currently be iOS-only (Android port in progress).

---

### Chapter 12 — Shadows, particles, transform feedback, depth

- **`ShadowMapping`**: classic shadow map pipeline.
- **`PCF_AntiAliasedShadows`**: PCF filtered shadows.
- **`VarianceShadowMapping`**: VSM technique and its tradeoffs.
- **`ViewingDepthTexture`**: visualizing depth textures and debugging depth.
- **`TransformFeedback`**: GPU-side capture of vertex outputs for reuse.
- **`ParticleSystem`**: particles and update/render organization.

**You will learn / experiment with:** depth precision and bias, soft-shadow filtering, alternate shadow techniques, and using the GPU to generate/update data.

Notes:
- `OpenGL ES 3.0 Cookbook/SourceRepository/Chapter12/Known_Issues.txt` indicates these recipes may currently be iOS-only (Android port in progress).

---

### Building / running

Most recipes include platform-specific wrappers (commonly `Android/` and/or `iOS/`) plus shared code. Build using the platform project in that recipe folder and then modify the shaders/constants to explore:

- **Shader knobs**: kernel sizes, thresholds, specular power, light positions, distortion strength, blur radius.
- **State knobs**: depth func, cull mode, blend mode, texture filtering, FBO formats.
- **Performance knobs**: number of instances, texture resolution, number of passes.

