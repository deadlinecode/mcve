# Bun FFI MCVE (Minimum Complete Verifiable Example)

To run this example, you need to have [Bun](https://bun.sh/) installed on windows. (no linx or mac, no wsl)

```bash
bun run index.ts
```


## Files

- `index.ts`: The entry point of the program.
- `main.cpp`: The C++ code that is compiled into a DLL.
- `MCVE.dll`: The DLL that is loaded by the program (compiled from `main.cpp` via visual studio).