# Chapter 1

**Design** is defined as the process of formulating the maximum alternative solutions to a problem and selecting the best one.

## Levels of Design

### Interface Design
This phase defines how various modules, components, or users interact with the system. It specifically identifies the necessary inputs, outputs, and communication rules for these interactions.

### Architectural Design
This level establishes the overall structure of the system. It focuses on identifying the major components and determining how they are organized, connected, and communicate with one another.

### Detailed Design
This phase focuses on the internal logic of each individual component. It describes the specific algorithms, data structures, and step-by-step processing required for actual implementation.

---

# Chapter 2 — Software Design Principles and Philosophies

## 1. Guiding Principles for Modularization

When dividing a system into modules, engineers must use "guiding principles" to decide how to partition the software. Two notions characterize a well-designed module:

- **High Cohesion** — A measure of intra-module dependency, or the degree of internal dependability within a module's elements. A cohesive module performs a limited, specific task.
- **Low Coupling** — A measure of inter-module dependency, or how much different modules connect to or rely on one another. The goal is to decrease these dependencies to make modules more independent.

## 2. Information Hiding (Encapsulation)

Considered a "better modularization approach," this principle involves specifying and designing modules so that internal information (such as algorithms and data) is inaccessible to other modules that do not need it. It isolates changeable parts, making them a "secret" of the module to prevent errors from spreading.

## 3. Functional Independence

This principle states that every module should address a specific sub-function of the requirements and maintain a simple interface. Independent modules are easier to maintain, test, and develop because the impact of changes or errors is localized.

## 4. Abstraction and Refinement

These are complementary features used to manage design complexity:

- **Abstraction** — Focuses on representing essential features while hiding lower-level details or background explanations.
- **Refinement** — A top-down design strategy where a high-level functional statement is incrementally elaborated until actual programming language statements are reached.

## 5. Software Architecture and Patterns

- **Architecture** — The principle is to derive an architectural rendering of the system to serve as a framework for more detailed design. It provides "conceptual integrity" for the system.
- **Patterns** — Standardized, reusable solutions to recurring problems. Learning these allows even inexperienced developers to learn design more quickly.

---

## Summary: A Well-Formed Design

Based on the application of these principles, a well-formed software design should be:

- Complete
- Clear
- Understandable
- Characterized by **high cohesion** and **low coupling**