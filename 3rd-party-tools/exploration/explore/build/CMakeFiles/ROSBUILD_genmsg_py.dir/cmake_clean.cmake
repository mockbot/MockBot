FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/explore/msg"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/explore/msg/__init__.py"
  "../src/explore/msg/_ExploreState.py"
  "../src/explore/msg/_ExploreGoal.py"
  "../src/explore/msg/_ExploreFeedback.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
