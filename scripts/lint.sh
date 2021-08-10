#!/usr/bin/env bash

set -e
set -o pipefail

usage() {
  echo "usage: lint.sh [[[-c continue ] [-p path]] | [-h]]"
}

base_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"/
inspect_path="$base_dir"
continue_on_error=false

while [ "$1" != "" ]; do
  case $1 in
  -p | --path)
    shift
    inspect_path=$1
    ;;
  -c | --continue)
    continue_on_error=true
    ;;
  -h | --help)
    usage
    exit
    ;;
  *)
    usage
    exit 1
    ;;
  esac
  shift
done

if [[ -d "$inspect_path" ]]; then
  SUCCESS=true
  while read -r file_path; do
    file_path=$(realpath "$file_path")
    set -e
    EXIT_CODE=0
    diff -u "$file_path" <(
      (
        cd "$base_dir" || exit 1
        clang-format -style=file "$file_path" --verbose
      )
    ) || EXIT_CODE=$?

    if [ "$EXIT_CODE" != "0" ]; then
      if [ "$continue_on_error" != "true" ]; then
        exit 42;
      else
        SUCCESS=false
      fi
    fi
  done < <(find -L "$inspect_path" -not -path "*/*build*/*" -not -path "*/CMakeFiles/*" -name "*.cpp" -o -name "*.[ch]" -not -path "*/*build*/*" -not -path "*/CMakeFiles/*" )
  if [ "$SUCCESS" != "true" ]; then
    exit 42;
  fi
else
  inspect_path=$(realpath "$inspect_path")
  diff -u "$inspect_path" <(
    (
      cd "$base_dir" || exit 1
      clang-format -style=file "$inspect_path" --verbose
    )
  )
fi
