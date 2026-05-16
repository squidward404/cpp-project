PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE products
(
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    category TEXT,
    price REAL NOT NULL,
    quantity INTEGER NOT NULL,
    expiry_date TEXT
);
INSERT INTO products VALUES(1000,'Sample Product','Test',9.99,5,'2026-12-31');
COMMIT;
