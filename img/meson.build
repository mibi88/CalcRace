assets_sources = [
  'arrow.png',
  'favicon.png',
  'font_small.png',
  'font.png',
  'world1.png',
  'world2.png',
  'world3.png',
  'cars_skin1.png',
  'backgrounds/title.png',
  'backgrounds/map_choosing_screen.png',
  'backgrounds/end.png'
]

pymod = import('python')

prog_python = pymod.find_installation('python3',
  required: true,
  modules: [
    'sys',
    'PIL',
    'os',
  ],
)

calcrace_sources = []

foreach image : assets_sources
  calcrace_sources += custom_target(
    output: '@BASENAME@.c',
    input: image,
    command: [prog_python, img_converter,
      '@INPUT@',
      meson.current_build_dir()+'/@BASENAME@.h',
      '@OUTPUT@'],
    build_by_default: true
  )
endforeach

if target_machine.system() == 'wasm'
  configure_file(input: 'favicon.png',
    output: 'favicon.png',
    copy: true,
    install_dir: meson.project_build_root(),
    install: true,
  )
endif
