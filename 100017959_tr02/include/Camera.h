// @file   Camera.h
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Camera moves the screen by following a game object.

#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"
#include "Point.h"
#include "Vector.h"

class Camera
{
  public:
    // Registers the object that the camera will follow.
    static void Follow(GameObject* focus);

    // Stops following the registered object.
    static void Unfollow();

    // Updates camera position with the registered object position.
    static void UpdatePositionByFocusObject();

    // Updates camera position by calculating displacement with camera speed.
    static void UpdatePositionBySpeed(float dt);

    // Updates camera position given a time interval.
    static void Update(float dt);

    // Camera position (in pixels).
    static Point position;

    // Camera speed (in pixels/second).
    static Vector speed;
  private:
    // Current object that the camera follows.
    static GameObject* focus;
};

#endif // CAMERA_H_