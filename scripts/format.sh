#!/usr/bin/env bash

set -e
set -o pipefail

base_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
file_list=()

while read -r file_path; do
  file_list+=("$file_path")
done < <(find -L "$base_dir" -not -path "*/*build*/*" -not -path "*/CMakeFiles/*" -name "*.cpp" -o -name "*.[ch]" -not -path "*/*build*/*" -not -path "*/CMakeFiles/*" )

(
  cd "$base_dir" || exit 1
  clang-format -style=file "${file_list[@]}" -i --verbose
)
