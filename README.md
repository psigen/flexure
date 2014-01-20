Flexure
=======

A prototype of a low-overhead middleware layer for fast configuration
and IPC in real-time.

This is only a prototype.  Do not use this in production code.

Examples
--------

Different ways of getting and setting values into ``/apple/orange``:
```c++
flex = new Flexure("/");
*flex["apple"]["orange"] = 2.0;
*flex["apple/orange"] = 2.1;
*flex["apple//orange"] = 2.2;
*flex["/apple/orange"] = 2.3;
*(new Flexure("/apple"))["orange"] = 2.4;
*(new Flexure("apple"))["orange"] = 2.5;

int orange = *flex["apple"]["orange"];
std::cout << "Orange is '"
          << orange << "'" << std::endl;
// Prints "Orange is '2.5'"
```

Remapping namespaces at runtime:
```c++
flex = new Flexure("apple");
flex.remap("orange", "/pear");
*flex["orange"] = 2.0; // Sets /pear = 2.0
*flex["/orange"] = 2.0; // Sets /orange = 2.0
*flex["mango"] = 2.0; // Sets apple/mango = 2.0
```

Registering a callback when a node changes values:
```c++
void callback(Flexure f, value) {
  std::cout << "Changed to '" 
            << new_val << "'" << std::endl;
}

flex = new Flexure("/");
*flex["apple"]["orange"] = 1.0;

flex["apple"]["orange"].Observe(callback);
*flex["apple"]["orange"] = 2.0;
// Prints "Changed to '2.0'"

flex["apple"]["orange"].Unobserve(callback);
*flex["apple"]["orange"] = 0.0;
// No output
```

Locking a hierarchy for read persistence:
```c++
Flexure f = flex["apple"];
Flexure f2 = flex["apple"];
*f = 2.0;

f.Lock();

int apple = *f;
std::cout << "Apple is '"
          << apple << "'" << std::endl;
// Prints "Apple is '2.0'"

*f = 2.5;
*f2 = 3.0;

int apple = *f;
std::cout << "Apple is '"
          << apple << "'" << std::endl;
// Prints "Apple is '2.5'"

f.Unlock();

int apple = *f;
std::cout << "Apple is '"
          << apple << "'" << std::endl;
// Prints "Apple is '3.0'" OR "Apple is '2.5'"
```

Transacting a hierarchy for atomic updates:
```c++
Flexure f = flex["apple"];
f.BeginTransaction();
*f = 2.0;
*f["apple"] = false;
*f["pear"] = "Pear";
f.EndTransaction();
```