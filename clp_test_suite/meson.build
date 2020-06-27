project('ggc', ['c', 'cpp'],
  default_options: [
  'warnlevel=3',
  'debug=true',
  'c_std=c11',
  'b_sanitize=address',
  ])

src = [
  'src/tok_vec.c',
  'src/lexer.c',
  'src/parser.c',
]

tests = [
  'test-lexer.cpp',
  'test-parser.cpp',
  'test-tok-vec.cpp',
]

clp_inc = include_directories('include')

clp_so = library('clp', src, include_directories: clp_inc)
clp_dep = declare_dependency(link_with: clp_so)

gtest_dep = dependency('gtest')

foreach test_src: tests
  bin = executable('bin' + test_src, 'tests/' + test_src,
    dependencies: [
      clp_dep,
      gtest_dep],
    include_directories: clp_inc)
  test('bin' + test_src, bin, args: [
    '--gtest_color=yes',
    ])
endforeach
