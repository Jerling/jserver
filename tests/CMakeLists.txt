find_package (Threads)
set(LINK_LISTS
  ${LINK_LISTS}
  ../third_part/glog/.libs
  ../third_part/benchmark/build/lib
  )
link_directories(${LINK_LISTS})
set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(../src/jbase/fs SRC_LISTS)
aux_source_directory(../src/jbase/conf SRC_LISTS)
aux_source_directory(../src/jbase/log SRC_LISTS)
aux_source_directory(../src/jbase/buffer SRC_LISTS)

aux_source_directory(../src/jnet/poller SRC_LISTS)
aux_source_directory(../src/jnet/listener SRC_LISTS)
aux_source_directory(../src/jnet/connect SRC_LISTS)

# add_executable(fs_test fs_test.cpp ${SRC_LISTS})
# target_link_libraries(fs_test gtest ${CMAKE_THREAD_LIBS_INIT})

# add_executable(conf_test conf_test.cpp ${SRC_LISTS})
# target_link_libraries(conf_test gtest ${CMAKE_THREAD_LIBS_INIT})

# add_executable(log_test logging_test.cpp ${SRC_LISTS})
# target_link_libraries(log_test ${EXTRA_LIBS})

add_executable(poller_test poller_test.cpp ${SRC_LISTS})
target_link_libraries(poller_test ${EXTRA_LIBS})

add_executable(poller_test_cli poller_test_cli.cpp ${SRC_LISTS})
target_link_libraries(poller_test_cli ${EXTRA_LIBS})
