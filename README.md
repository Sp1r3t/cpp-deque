# Qt Deque Explorer

**Qt Deque Explorer** is a C++ educational application developed with the Qt framework to demonstrate the functionality of the `std::deque` container and various Standard Template Library (STL) algorithms. This project visualizes real-time container manipulation, iterator management, and custom sorting implementations.

---

## Features

### Container Operations
- **Dynamic Modification:** Supports standard double-ended queue operations including `push_front`, `push_back`, `pop_front`, and `pop_back`.
- **Element Management:** Users can insert elements at the current iterator position, erase specific elements, or clear the entire container.
- **Resizing:** Allows manual adjustment of the container size using the `resize` method.

### Iterator Control
- **Navigation:** Move through the deque using increment (`++`) and decrement (`--`) buttons.
- **Direct Access:** Jump immediately to the `begin()` or `end()` positions of the container.
- **In-place Editing:** Modify the content of the element currently pointed to by the iterator.

### Algorithms
The project showcases several STL and custom algorithms:
- **Search & Statistics:** Find specific values, count occurrences, or locate `min_element` and `max_element`.
- **Data Transformation:** Includes `shuffle` for randomization, `reverse` for flipping element order, and `unique` for removing consecutive duplicates.
- **Binary Search:** Integrated `lower_bound` and `upper_bound` functionality for sorted data.
- **Sorting:** Features a custom recursive **Merge Sort** implementation, including a case-insensitive sorting option.

---

## Technical Stack
- **Language:** C++20
- **Framework:** Qt 6 (Widgets module)
- **Container:** `std::deque<std::string>`
- **Build System:** qmake

---

## Project Structure
- `algo.h` – Contains the template implementation for the recursive Merge Sort algorithm.
- `model.h` – Defines the `Model` struct which holds the `std::deque` and its associated iterator.
- `mainwindow.cpp/h` – Manages the GUI logic, event handling, and synchronization between the UI and the data model.
- `mainwindow.ui` – The XML-based layout definition for the graphical interface.

---

## Predefined Data Sets
For testing purposes, the application includes two quick-fill templates:
- **Tea:** Populates the deque with various types of tea such as `"Lapsang Souchong"` and `"Matcha"`.
- **Cakes:** Populates the deque with dessert names like `"Napoleon"` and `"Tiramisu"`.
