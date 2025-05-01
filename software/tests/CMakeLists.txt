include(FetchContent)

# Setup Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/04ee1b4f2aefdffb0135d7cf2a2c519fe50dabe4.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Compile test
add_executable(test
  test-midi-msg.cc
  test-track.cc
  test-mackie-msg.cc
  test-mcu-sys-msg-fsm.cc
  test-mackie-protocol.cc
)

# Link GTest and pthread
target_link_libraries(test
  gmock
  gtest_main
  pthread
  midixer
)
