#!/usr/bin/env python
import os
import sys

env = SConscript("godot_cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["dogcalc_ext/"])

# enable exceptions with -fexceptions
env.Append(CCFLAGS=["-fexceptions"])

sources = Glob("dogcalc_ext/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "ext/bin/libdogcalc.{}.{}.framework/libdogcalc.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "ext/bin/libdogcalc{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
