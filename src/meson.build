calcrace_sources = [
  'map.c',
  'tiles.c',
  'text.c',
  'calc.c',
  'player.c',
  'game.c',
  'memory.c',
  'keyboard.c',
  'touch.c',
  'main.c',
]

calcrace_incdirs = include_directories('../inc',
  '../lib',
)

if meson.get_compiler('c').get_id() == 'emcc'
  extra_args = [
    '-s WASM=2',
    '-s EXPORT_ALL=1',
    '-s ERROR_ON_UNDEFINED_SYMBOLS=0',
  ]
else
  extra_args = []
endif

if target_machine.system() != 'wasm'
  calcrace_deps = [
    meson.get_compiler('c').find_library('m', required: true),
  ]
else
  calcrace_deps = []
endif

executable('CalcRace', calcrace_sources,
  include_directories: calcrace_incdirs,
  link_whole : canvaslib,
  override_options: ['b_lundef=false'],
  link_args: extra_args,
  dependencies: calcrace_deps,
  install_dir: meson.project_build_root(),
  install: true,
)

if target_machine.system() == 'wasm'
  configure_file(input: 'run.sh',
    output: 'run.sh',
    copy: true,
    install_dir: meson.project_build_root(),
    install: true,
  )
  configure_file(input: 'CalcRace.html',
    output: 'index.html',
    copy: true,
    install_dir: meson.project_build_root(),
    install: true,
  )
endif
