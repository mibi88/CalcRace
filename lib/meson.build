canvaslib_sources = [
  'canvas.c',
  'image.c',
  'audio.c',
]

if target_machine.system() != 'wasm'
  canvaslib_deps = [
    dependency('sdl', native: true),
  ]
else
  canvaslib_deps = []
endif

canvaslib_incdirs = include_directories('.')

canvaslib = static_library('canvaslib', canvaslib_sources,
  dependencies: canvaslib_deps,
  include_directories: canvaslib_incdirs,
)
