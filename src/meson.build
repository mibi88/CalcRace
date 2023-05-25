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

executable('CalcRace', calcrace_sources,
  include_directories: calcrace_incdirs,
  link_whole : canvaslib,
  override_options: ['b_lundef=false'],
  link_args: extra_args,
)

configure_file(input: 'run.sh',
  output: 'run.sh',
  configuration: configuration_data(),
)

configure_file(input: 'CalcRace.html',
  output: 'index.html',
  configuration: configuration_data(),
)
