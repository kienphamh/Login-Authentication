# Login-Authentication
A simple login authentication program written in C++

The password hash used was from ![libbcrypt](https://github.com/trusch/libbcrypt)

The file **stored-creds.txt** is present only for demonstration purposes, it's best to add it to .gitignore

## Compilation

### Linux/macOS/WSL:
```bash
g++ -o <output-name> <source-file> -lbcrypt -std=c++23
or
clang++ -o <output-name> <source-file>  -lbcrypt -std=c++23
```

### Windows (MinGW):
```cmd
g++ -o <output-name> <source-file>  -lbcrypt -std=c++23
```

### Windows (MSVC):
```cmd
cl /EHsc /std:c++23 <source-file>  /link bcrypt.lib
```
