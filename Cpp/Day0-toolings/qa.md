**1. Compiler Flags: Sanitizers vs. Benchmarks**

* **Sanitizers (Debugging):** Use **`-O1 -g -fno-omit-frame-pointer`**.
* **Why:** `-O1` provides a practical balance between execution speed and debuggability. `-g` links machine code back to source lines. `-fno-omit-frame-pointer` forces the CPU to keep the frame pointer, allowing the sanitizer to instantly unwind and print a flawless, readable stack trace when it catches an error.
* *Reference:* [Intel oneAPI: Find Bugs Quickly Using Sanitizers](https://www.intel.com/content/www/us/en/developer/articles/technical/find-bugs-quickly-using-sanitizers-with-oneapi-compiler.html)


* **Benchmarks (Performance):** Use **`-O2`** or **`-O3`**.
* **Why:** Unleashes aggressive compiler optimizations (inlining, loop unrolling, vectorization) to measure the true performance limits of your code for production.


* **Consequences of Mixing:**
* *Sanitizers with `-O3`:* The compiler actively rewrites code and may entirely delete the bug via Dead Code Elimination, causing the sanitizer to miss it. Even if caught, heavy inlining destroys the stack trace, making debugging nearly impossible.
* *Benchmarks with `-O0`/`-O1`:* Yields useless, artificially slow execution times that do not reflect real-world bottlenecks.



**2. CMake's Role in the Compilation Pipeline**

* **The Core Distinction:** CMake is a **Build System Generator**, not a compiler. It does *not* execute the 4 pipeline steps (Preprocessing $\rightarrow$ Compilation $\rightarrow$ Assembling $\rightarrow$ Linking).
* **Its Role:** It reads your `CMakeLists.txt` and generates the actual build scripts (like `Makefile` or `build.ninja`) that will orchestrate the compiler (e.g., `clang++`).
* **Practical Value:**
* **Intelligent Incremental Builds:** Tracks file timestamps and header dependencies. Advanced generators like Ninja even track command-line changes (e.g., swapping from `-O1` to `-O3`). It selectively rebuilds *only* the affected files rather than the whole project.
* **Flag Consistency:** Acts as a single source of truth, ensuring every `.cpp` file in a massive project receives the exact same compiler flags automatically.
* *Reference:* [Make, CMake, and Embedded Build Systems](https://embeddedinterviewlab.com/topics/make-cmake-embedded/)