# auto_system_core

## How to build
1. Start Dev Container
    ```bash
    git clone git@github.com:takanotaiga/auto_system_core.git
    cd auto_system_core
    git clone https://github.com/takanotaiga/gtest.git third_party/gtest
    ./run.sh
    ```
2. Compile with buck2
    ```bash
    buck2 build //...
    ```