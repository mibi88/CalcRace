project('CalcRace', 'c',
          version: 'v.0.5-git',
    meson_version: '>= 0.60.0',
  default_options: [ 'warning_level=2',
                     'c_std=c89',
                   ],
)

config_h = configuration_data()
config_h.set_quoted('GAME_VERSION', meson.project_version())
configure_file(
  output: 'config.h',
  configuration: config_h,
)
add_project_arguments([
  '-I' + meson.project_build_root(),
  '-I' + meson.project_build_root() + '/img',
], language: 'c')

subdir('img')
subdir('lib')
subdir('src')
