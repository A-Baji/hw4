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
* Check if instersect is within the triangle
  * If not then no hit
  * Otherwise, return the HitRecord with the newly calculated t, position, and normal values
  
**Problem 2**
  
For problem 2 we had to implement phong shading for our objects. To do this I created a new function in the Scene class called phongShading that takes a HitRecord object, a Vector, and a double as parameters and then returns a vector with the correct shading. The HitRecord object holds the normal and position. The vector is the light direction, and the double is our object color. These are all calculated in the trace function of the Scene class, and then phongShading is called in the trace function using those values.

In the phongShading function, I used the same math and code as I did in homework 3 and converted it to eigen vectors. I used (0, 0, 0) for the viewPos, (1, 1, 1) for lightColor, and the double parameter for objectColor. Then I calculate ambient light, diffuse light, and specular light. Then I added them all together, multiplied it by the object color and return the value.

**Problem 3**

For problem 3 we had to add shadow casting to our objects. To do this is really simple. In the trace function of the Scene class, we create a reference Ray object and set its origin to the position of our HitRecord object, and the direction as our lightDir vector. Then in a for loop we use this reference Ray to check for the closest hit, and if there is something between the position and light source then we return the result as black for shadow.
