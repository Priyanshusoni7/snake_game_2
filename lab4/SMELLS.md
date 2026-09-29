# Test smells — the short list

- **Mystery guest:** input is hidden in a file, database, or distant fixture.
- **Resource optimism:** the test assumes an environment or resource it did not create.
- **General fixture:** shared setup contains data most tests do not use.
- **Eager test:** one test exercises several behaviours.
- **Assertion roulette:** repeated assertions lack useful case diagnostics.
- **A test that asserts nothing:** its assertion passes regardless of meaningful behaviour.
