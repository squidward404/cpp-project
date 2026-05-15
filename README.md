# Inventory Project

Simple C++ inventory manager using SQLite for storage. This repository contains the source code, a SQL dump and a CSV export of the `products` table for portability.

**Files of interest**
- [inventory.cpp](inventory.cpp): main program source 
- [.gitignore](.gitignore): ignores `inventory.db` and build artifacts
- [dump.sql](dump.sql): SQL dump of the `inventory.db` (schema + data)
- [products.csv](products.csv): CSV export of the `products` table
- [CONTRIBUTIONS.md](CONTRIBUTIONS.md): project contributions of each member

**Build**
Install `sqlite3` development headers and a C++ toolchain, then compile:

```bash
g++ inventory.cpp -o inventory -lsqlite3 -std=c++17
```

**Run**
Run the binary: it will create/use `inventory.db` in the working directory:

```bash
./inventory
```

**Sample data**
A small sample product was added locally for convenience(see `products.csv`.)

**Group Information**
- Section: A
- Group Number: 10
- Course: Fundamentals of programming II
- Department: Software Engineering, AASTU
- Instructor: Eleni Teshome

**Group Members**

- Blen Mekonnen (ETS 0357/17)
- Biniam Girma (ETS 0312/17)
- Eden Wubshet (ETS 0461/17)
- Abemelek Samson (ETS 0043/17)
- Adonias Hailu (ETS 0103/17)
- Befikir Shimelis (ETS 0237/17)


