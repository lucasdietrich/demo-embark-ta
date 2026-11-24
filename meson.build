project('myta', 'c',
  version: '0.1.0',
  default_options: [
    'c_std=c11',
    'buildtype=debug',
    'warning_level=3',
    'werror=false',
    'default_library=shared'
  ],
)

dependencies = [
  dependency('teec'),
]

sources = [
  'src/myta.c',
]

include_directories = [
  'ta/include',
  'include',
]

install_headers(
  'include/myta.h',
  # subdir: 'include/myta',
)

project_lib = library(
  meson.project_name(),
  sources,
  dependencies: dependencies,
  include_directories: include_directories,
  install: true,
  install_dir: 'lib',
)


# Demo application using the client library
executable(
  'myta-demo',
  'examples/demo.c',
  include_directories: include_directories('include'),
  link_with: project_lib,
  install: true,
  install_dir: 'bin',
)

