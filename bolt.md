
## 2024-07-16 – Efficient File Reading in `SourceFile`
Learning: The initial implementation of `SourceFile::SourceFile` read files line by line using `std::getline`, which resulted in a separate memory allocation for each line. This approach is inefficient for large files and can lead to performance degradation due to increased memory allocations and poor cache locality.
Action: By reading the entire file into a single `std::string` buffer and then creating `std::string_view`s for each line, we can significantly reduce the number of allocations and improve cache performance. This is a more efficient approach for handling file I/O in C++.
