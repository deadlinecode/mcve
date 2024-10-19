import { dlopen, FFIType, JSCallback } from "bun:ffi";
import os from "os";

if (os.platform() !== "win32") throw new Error("Only windows is supported");

// Stop the program from exiting for 10 seconds
setTimeout(() => {}, 10000);

const lib = dlopen("MCVE.dll", {
  onChange: {
    args: ["callback"],
    returns: FFIType.bool,
  },
});

lib.symbols.onChange(
  new JSCallback(
    (val: number) => {
      console.log("Got callback", val);
      return true;
    },
    {
      args: [FFIType.int32_t],
      returns: FFIType.bool,
    }
  ).ptr
);
