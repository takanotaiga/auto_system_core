# Inter-Process Communication


## posix_shm_close

オープンになっている共有メモリを閉じます。リソースがプロセスから解放されます。

::: warning
リソースはシステムからは解放されません。
:::

### 定義

`auto_system_api/include/auto_system_api/backend/ipc_backend.hpp`

```c++
void posix_shm_close(void * ptr, int64_t size, int fd);
```

### パラメーター

- **`ptr`**: 
閉じたい共有メモリのポインタ

- **`size`**: 
閉じたい共有メモリのサイズ

- **`fd`**: 
閉じたい共有メモリのファイルディスクリプタ


### 戻り値
この関数は値を返しません。

### 例外
この関数は例外を投げません。


## posix_shm_allocate

共有メモリを確保します。確保した領域は全て0で埋められます。

### 定義

`auto_system_api/include/auto_system_api/backend/ipc_backend.hpp`

```c++
void posix_shm_allocate(const std::string & name, int64_t size);
```

### パラメーター

- **`name`**: 
パイプラインの名前。lower_snake_caseのみ使用できます。

- **`size`**: 
共有メモリのサイズ。


### 戻り値
この関数は値を返しません。

### 例外
- 領域が確保できなかった場合
- 不正なパイプライン名が設定された場合


## posix_shm_get_addr
共有メモリのポインタを入手します。

### 定義

`auto_system_api/include/auto_system_api/backend/ipc_backend.hpp`

```c++
auto posix_shm_get_addr(const std::string & name, int64_t size, bool is_write = false)
  -> std::pair<void *, int>;
```

### パラメーター

- **`name`**: 
パイプラインの名前。lower_snake_caseのみ使用できます。

- **`size`**: 
共有メモリのサイズ。

- **`is_write`**: 
書き込み可能かを決めるフラグ。`true=書き込み可能`、`false=書き込み不可`。

### 戻り値
- **`std::pair<void *, int>`**: 
共有メモリのポインタとファイルディスクリプタのペア。

### 例外
- 存在しないパイプラインを指定した場合
- `size`が実態よりオーバーフローしていた場合

## posix_shm_remove
共有メモリパイプラインを完全に削除します。

### 定義

`auto_system_api/include/auto_system_api/backend/ipc_backend.hpp`

```c++
void posix_shm_remove(const std::string & name);
```

### パラメーター

- **`name`**: 
パイプラインの名前。lower_snake_caseのみ使用できます。

### 戻り値
この関数は値を返しません。

### 例外
- 存在しないパイプラインを指定した場合

## posix_shm_name_check
与えられたパイプライン名が正しいかを確認します。

### 定義

`auto_system_api/include/auto_system_api/backend/ipc_backend.hpp`

```c++
void posix_shm_name_check(const std::string & name);
```

### パラメーター

- **`name`**: 
パイプラインの名前。

### 戻り値
この関数は値を返しません。

### 例外
- 128文字以上の場合
- lower_snake_case以外の文字列が渡された場合
