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

foreach image : assets_sources
  custom_target(
    output: '@BASENAME@.h',
    input: image,
    command: [prog_python, '../tools/imgconv.py', '@INPUT@', '@OUTPUT@'],
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
