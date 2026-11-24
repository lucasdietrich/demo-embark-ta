#!/bin/bash
find src \( -iname '*.h' -o -iname '*.c' -o -iname '*.cpp' -o -iname '*.hpp' \) -print0 | xargs -0 -r clang-format -i
find include \( -iname '*.h' -o -iname '*.c' -o -iname '*.cpp' -o -iname '*.hpp' \) -print0 | xargs -0 -r clang-format -i

