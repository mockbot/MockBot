FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/explore/msg"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/explore/ExploreState.h"
  "../msg_gen/cpp/include/explore/ExploreGoal.h"
  "../msg_gen/cpp/include/explore/ExploreFeedback.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
