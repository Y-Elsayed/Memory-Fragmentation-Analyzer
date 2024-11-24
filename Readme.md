# Memory Fragmentation Analyzer

A **C-based proof-of-concept tool** designed to detect and analyze memory fragmentation in a given memory allocation scenario. The analyzer evaluates internal and external fragmentation, provides statistical insights, and suggests solutions to optimize memory usage.

## Features
- **Internal Fragmentation Detection**  
  Calculates unused memory within allocated blocks.

- **External Fragmentation Detection**  
  Identifies memory gaps that are too small to satisfy allocation requests.

- **Statistical Reporting**  
  Outputs detailed metrics on:
  - Total memory allocated
  - Memory wasted due to fragmentation
  - Memory utilization percentage

- **Optimization Suggestions**  
  Recommends techniques to minimize fragmentation, such as:
  - Memory compaction
  - Alternative allocation strategies (e.g., best-fit, first-fit)

