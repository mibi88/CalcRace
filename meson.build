project('CalcRace', 'c',
          version: 'v.0.5-git',
    meson_version: '>= 0.59.0',
  default_options: [ 'warning_level=2',
                     'c_std=c89',
                   ],
)

config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
configure_file(
  output: 'config.h',
  configuration: config_h,
)
add_project_arguments([
  '-I' + meson.project_build_root(),
], language: 'c')

pymod = import('python')

py3 = pymod.find_installation('python3', required: true)
py3.dependency('sys')
py3.dependency('Pillow')
py3.dependency('os')

script = configure_file('tools/imgconv_dir_term.py')

custom_target(
  command: [py3, script, 'img/', 'img_conv/']
)
custom_target(
  command: [py3, script, 'img/cars/skin1/', 'img_conv/']
)

subdir('lib')
subdir('src')
