Flexure
=======

A prototype of a low-overhead middleware layer for fast configuration
and IPC in real-time.

This is only a prototype.  Do not use this in production code.

Examples
--------
```c++
flex = new Flexure("/");
flex["apple"]["orange"] = 2.0;
```

```c++
void callback(Flexure f, Value old_val, Value new_val) {
  std::cout << "Changed from '" 
            << old_val << "' to '" 
            << new_val << "'" << std::endl;
}

flex = new Flexure("/");
flex["apple"]["orange"].addCallback(callback);
```