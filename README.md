# hw4
COSC 4370 Homework 4

PSID: 1776794

## Environment:
* OS: Windows 10

* Language: C++

* IDE: Visual Studio

## Report

**Problem 1**

For problem 1 we had to add a new shape to the scene. I added a triangle and replaced the small sphere on the right with a triangle. To do this I had to add a Triangle.h and Triangle.cpp.

In Triangle.h, we simply have a constructor, a HitRecord function for the intersect with a reference to a Ray object as parameter, and 3 vectors for each point of the triangle. In the constructor, we set our 3 vectors as the 3 vectors passed in the constructor.

In Triangle.cpp, we define our intersect function:
* Calculate the normal
* Check if the ray and plane are parallel
 * If they are then there is no hit
* Check if the triangle is behind the ray
 * If it is then there is no hit
* Calculate position of intersect point
* Check if instersect is within triangle
 * If not then no hit
 * Otherwise, return the HitRecord with the newly calculated t, position, and normal values
