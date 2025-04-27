project(uorb_example_c_pub_sub)

add_executable(${PROJECT_NAME} c_pub_sub.c)
target_link_libraries(${PROJECT_NAME} PRIVATE slog)
target_link_libraries(${PROJECT_NAME} PRIVATE uorb_examples_msgs)

# pthread
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


add_executable(pubcpp pub.cpp)
target_link_libraries(pubcpp PRIVATE slog)
target_link_libraries(pubcpp PRIVATE uorb_examples_msgs)

add_executable(pub pub.c)
target_link_libraries(pub PRIVATE slog)
target_link_libraries(pub PRIVATE uorb_examples_msgs)

add_executable(sub sub.c)
target_link_libraries(sub PRIVATE slog)
target_link_libraries(sub PRIVATE uorb_examples_msgs)