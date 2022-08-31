file(REMOVE_RECURSE
  "/Users/natesesti/Documents/Languages/rust/cppcas/CMake/bin/foo-cpu"
  "/Users/natesesti/Documents/Languages/rust/cppcas/CMake/bin/foo-cpu.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/foo-cpu.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
