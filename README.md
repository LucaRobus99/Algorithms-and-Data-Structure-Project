# 📚 Algorithms and Data Structures Project

This repository contains a collection of laboratory exercises and projects developed for the **Algorithms and Data Structures** course.

The project focus is both educational and experimental: each module is designed to study, implement, and rigorously test classic algorithms and fundamental data structures.

### 🎯 Key Objectives

* **Algorithmic Reasoning:** Translating theoretical models into efficient code.
* **Performance Analysis:** Benchmarking execution time and analyzing time/space complexity (Big O).
* **Systematic Testing:** Ensuring reliability through unit testing and edge-case validation.
* **Polyglot Development:** Utilizing **C** for low-level memory management and **Java** for object-oriented design.

---

## 📂 Project Structure and Exercises

### 1. Hybrid Sorting Algorithm (C)

Implementation of an optimized sorting strategy that combines **Merge Sort** and **Binary Insertion Sort**.

* **Logic:** The algorithm follows a recursive Merge Sort approach. When a subarray reaches a threshold size `k`, the system switches to Binary Insertion Sort.
* **Performance Tuning:** The project includes an empirical study to determine the optimal value of `k`, balancing the  efficiency of Merge Sort with the low constant factors of Insertion Sort on small datasets.

### 2. Skip List Dictionary & Spell Checker (C)

Implementation of a **Skip List**, a probabilistic data structure that provides efficient search and update operations.

* **The Structure:** A multi-layered linked list that allows "skipping" over elements, achieving an average time complexity of ****.
* **Application:** The Skip List is used to load a dictionary of valid Italian words. The system then processes a text file to identify and report spelling errors.
* **Scaling Analysis:** Evaluation of search performance as the dictionary size grows.

### 3. Generic Priority Queue (Java)

A robust and reusable implementation of a **Priority Queue** in Java.

* **Design:** The structure supports standard operations (insertion, extract-min, decrease-key) and is built to be used as a core component for more complex algorithms.
* **Generics:** Leverages Java Generics for maximum reusability across different data types.

### 4. Graph Theory & Prim's Algorithm (Java)

An advanced graph-based application focused on Minimum Spanning Forests (MSF).

* **Data Source:** The graph is constructed from a **CSV dataset** containing geographical distances between Italian locations.
* **The Algorithm:** Implementation of **Prim's Algorithm** using the previously developed Priority Queue.
* **Outcome:** Calculation of a Minimum Spanning Forest to connect nodes with the minimum total edge weight, accounting for potentially disconnected graph components.

---

## 🛠 Technologies & Tools

* **C:** Used for Exercises 1 and 2 to manage manual memory allocation and pointer-based structures.
* **Java:** Used for Exercises 3 and 4 to implement object-oriented patterns and complex graph logic.
* **CSV Parsing:** For handling real-world geographical data.
* **Unit Testing:** Comprehensive test suites for every module to ensure mathematical and logical correctness.

---

## 🏛 Academic Context

This project was developed as part of the **Algorithms and Data Structures** course at the **University of Turin (Università degli Studi di Torino)**.
