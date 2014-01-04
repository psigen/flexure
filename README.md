Flexure
=======

A prototype of a low-overhead middleware layer for fast configuration
and IPC in real-time.

This is only a prototype.  Do not use this in production code.

Examples
--------

Different ways of setting a value into ``/apple/orange``:
```c++
flex = new Flexure("/");
flex["apple"]["orange"] = 2.0;
flex["apple/orange"] = 2.0;
flex["apple//orange"] = 2.0;
flex["/apple/orange"] = 2.0;
(new Flexure("/apple"))["orange"] = 2.0;
(new Flexure("apple"))["orange"] = 2.0;
```

Remapping namespaces at runtime:
```c++
flex = new Flexure("apple");
flex.remap("orange", "/pear");
flex["orange"] = 2.0; // Sets /pear = 2.0
flex["/orange"] = 2.0; // Sets /orange = 2.0
flex["mango"] = 2.0; // Sets apple/mango = 2.0
```

Registering a callback when a node changes values:
```c++
void callback(Flexure f, Value old_val, Value new_val) {
  std::cout << "Changed from '" 
            << old_val << "' to '" 
            << new_val << "'" << std::endl;
}

flex = new Flexure("/");
flex["apple"]["orange"] = 1.0;

flex["apple"]["orange"].Observe(callback);
flex["apple"]["orange"] = 2.0;
// Prints "Changed from '1.0' to '2.0'"

flex["apple"]["orange"].Unobserve(callback);
flex["apple"]["orange"] = 0.0;
// No output
```
