# CMake generated Testfile for 
# Source directory: /home/teona/Documents/courses/CS660/cs660-pa/tests/pa2
# Build directory: /home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[BufferpoolTest.evictPage]=] "/home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2/pa2_test" "--gtest_filter=BufferpoolTest.evictPage")
set_tests_properties([=[BufferpoolTest.evictPage]=] PROPERTIES  SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]" TIMEOUT "5" _BACKTRACE_TRIPLES "/usr/local/share/cmake-3.27/Modules/GoogleTest.cmake;402;add_test;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;13;gtest_add_tests;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;0;")
add_test([=[BufferpoolTest.flushAllPages]=] "/home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2/pa2_test" "--gtest_filter=BufferpoolTest.flushAllPages")
set_tests_properties([=[BufferpoolTest.flushAllPages]=] PROPERTIES  SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]" TIMEOUT "5" _BACKTRACE_TRIPLES "/usr/local/share/cmake-3.27/Modules/GoogleTest.cmake;402;add_test;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;13;gtest_add_tests;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;0;")
add_test([=[BufferpoolTest.discardPage]=] "/home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2/pa2_test" "--gtest_filter=BufferpoolTest.discardPage")
set_tests_properties([=[BufferpoolTest.discardPage]=] PROPERTIES  SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]" TIMEOUT "5" _BACKTRACE_TRIPLES "/usr/local/share/cmake-3.27/Modules/GoogleTest.cmake;402;add_test;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;13;gtest_add_tests;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;0;")
add_test([=[BufferpoolTest.flushPage]=] "/home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2/pa2_test" "--gtest_filter=BufferpoolTest.flushPage")
set_tests_properties([=[BufferpoolTest.flushPage]=] PROPERTIES  SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]" TIMEOUT "5" _BACKTRACE_TRIPLES "/usr/local/share/cmake-3.27/Modules/GoogleTest.cmake;402;add_test;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;13;gtest_add_tests;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;0;")
add_test([=[BufferpoolTest.flushPages]=] "/home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2/pa2_test" "--gtest_filter=BufferpoolTest.flushPages")
set_tests_properties([=[BufferpoolTest.flushPages]=] PROPERTIES  SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]" TIMEOUT "5" _BACKTRACE_TRIPLES "/usr/local/share/cmake-3.27/Modules/GoogleTest.cmake;402;add_test;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;13;gtest_add_tests;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;0;")
add_test([=[BTreeFileTest.findLeafPage]=] "/home/teona/Documents/courses/CS660/cs660-pa/objects/tests/pa2/pa2_test" "--gtest_filter=BTreeFileTest.findLeafPage")
set_tests_properties([=[BTreeFileTest.findLeafPage]=] PROPERTIES  SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]" TIMEOUT "5" _BACKTRACE_TRIPLES "/usr/local/share/cmake-3.27/Modules/GoogleTest.cmake;402;add_test;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;13;gtest_add_tests;/home/teona/Documents/courses/CS660/cs660-pa/tests/pa2/CMakeLists.txt;0;")
subdirs("../../_deps/googletest-build")
