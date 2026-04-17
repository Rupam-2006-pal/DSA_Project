# AVL Tree in C with Graphical Visualization

## 📌 Overview

This project is an implementation of an **AVL Tree (Self-Balancing Binary Search Tree)** in C.
It not only performs standard AVL operations but also provides a **graphical visualization** of the tree structure using `graphics.h`.

The main goal of this project was to deeply understand:

* AVL balancing logic
* Tree rotations
* Practical visualization of hierarchical data structures

---

## ⚙️ Features

* Iterative insertion
* Automatic balance factor calculation
* All AVL rotations implemented:

  * LL (Left-Left)
  * RR (Right-Right)
  * LR (Left-Right)
  * RL (Right-Left)
* Deletion using subtree reinsertion (post-order)
* Inorder traversal
* Graphical display of tree structure

---

## 🧠 AVL Tree Logic

An AVL Tree maintains the balance factor:

Balance Factor = Height(Left Subtree) - Height(Right Subtree)

Valid range: `-1, 0, +1`

If violated, rotations are applied:

* LL → Right Rotation
* RR → Left Rotation
* LR → Left Rotation + Right Rotation
* RL → Right Rotation + Left Rotation

---

## 🖥️ Graphical Visualization

The project uses `graphics.h` (BGI library) to draw the AVL tree.

### Key Points:

* Nodes are drawn using `ellipse()`
* Values are printed using `outtextxy()`
* Edges are drawn using `line()`
* A 2D occupancy array is used to reduce overlapping

⚠️ Note:
Graphical output may sometimes overlap depending on tree shape. This is due to simple coordinate handling and can be further improved.

---

## 🚀 How to Run

### Requirements:

* **Dev-C++ (with graphics support)**
* `graphics.h` library installed

### Steps:

1. Install **Dev-C++**
2. Install/Configure `graphics.h` (WinBGIm or equivalent)
3. Copy the code into a .cpp (though this is a C code, it will be better to use .cpp for graphical code) file
4. Compile and run inside Dev-C++

---

## ⚠️ Important Note About Graphics

This code uses:

```
#include <graphics.h>
```

👉 You must install **`graphics.h`** in Dev-C++ to run the graphical part.

---

## 🧹 If You Don’t Want Graphical Code

If you only want the AVL logic (without graphics), you can safely remove the graphical parts.

### Remove/Comment the following:

1. Header files:

```
#include <graphics.h>
```

2. Graphical menu option:

```
case 4:  // Graphical Display
```

3. Function:

```
int graphical_display(...)
```

4. Graphics-related functions:

```
initwindow()
closegraph()
outtextxy()
ellipse()
line()
```

5. Any occupancy array usage:

```
int occupancy[WIDTH][HEIGHT];
```

After removing these, your program will work as a **pure AVL Tree implementation** and you can run with .c .

---

## 📚 Learning Outcomes

* Deep understanding of AVL balancing
* Implementation of tree rotations
* Handling dynamic tree restructuring
* Visualization challenges in tree structures
* Trade-offs between simplicity and efficiency

---

## 🔗 Future Improvements

* Better node spacing algorithm
* Level-based tree rendering
* GUI-based visualization instead of BGI
* Optimization (store height instead of recalculating)

---

## 🙌 Feedback

Suggestions and improvements are always welcome, especially for:

* Visualization enhancement
* Optimization techniques
* Cleaner AVL implementation

---

## 📎 Author

Rupam Pal
