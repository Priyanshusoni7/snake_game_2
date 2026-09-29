# Lab 4 test suite

Run both the unmodified `lab4-base` tests and the seam tests from the repository root:

```powershell
powershell -ExecutionPolicy Bypass -File lab4/run-tests.ps1 -Suite all
```

The script requires `g++`, `gcov`, and PowerShell. It checks out no files and writes generated sources, executables, and coverage data only under the ignored `lab4/build/` directory.

- `tests/baseline.cpp` tests the tagged source without changing it.
- `tests/seam.cpp` tests the object seam introduced in commit 1.
- `REPORT.md` contains the assignment report.
- `evidence/` contains the captured test and coverage summaries.
