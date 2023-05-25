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

'''
gen = generator(prog_python,
  output: '@BASENAME@.h',
  arguments: ['../tools/imgconv.py', '@INPUT@', '@OUTPUT@']
)

gen_src = gen.process(assets_sources)
'''
