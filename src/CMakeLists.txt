add_library( tennis SHARED
  checkCircle.cpp
  checkColour.cpp
  filter.cpp
  edge2list.cpp
  get_centroid.cpp
  get_Random_points.cpp
  movemet.cpp
  1.Method_of_exhaustion.cpp
  2.Greedy_Algorithm.cpp
  ProjectiveTransform.cpp
)


target_link_libraries( tennis
    ${THIRD_PARTY_LIBS}
)

add_executable( main main.cpp )
target_link_libraries( main tennis )

add_executable( Trajectory Trajectory.cpp )
target_link_libraries( Trajectory tennis )