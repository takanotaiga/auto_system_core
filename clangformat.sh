#!/bin/bash
set -e

format() {
  local TARGET_DIR="$1"

  if [ -z "$TARGET_DIR" ]; then
    echo "エラー: ディレクトリを指定してください。"
    return 1
  fi

  find "$TARGET_DIR" -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -i {} +
  echo "clang-format を適用しました: $TARGET_DIR"
}

format "./auto_system_api/include"
format "./auto_system_api/src"
format "./auto_system_api/test"