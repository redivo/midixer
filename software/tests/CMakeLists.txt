# Setup Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Compile test
add_executable(test
  test-midi-msg.cc
  test-track.cc
)

# Link GTest and pthread
target_link_libraries(test
  gtest_main
  midixer
)
