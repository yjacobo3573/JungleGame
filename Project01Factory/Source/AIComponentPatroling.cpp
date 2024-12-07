#include "AIComponentPatroling.h"

void AIComponentPatroling::draw()
{
}

void AIComponentPatroling::update()
{

float playerX=0;

for (auto& gameObjs : Engine::gameObjects) {

    if (gameObjs && gameObjs->getType() == "Player") { //if not null and type player

    auto body= gameObjs->get<BodyComponent>();
       if (body) {
            playerX= body->getX();
          }

     }
}


   float enemyX=0;
   float enemyVelocityX=0;

   auto bodyEnemy= parent().get<BodyComponent>();

   if (bodyEnemy) {
    enemyX= bodyEnemy->getX();
    enemyVelocityX= bodyEnemy->getVelocityX();
    }


  int distance=0;


  distance= enemyX-playerX;



if (distance <= 621)
{
    
    static bool movingLeft = true; // Tracks the current direction

    const float leftBoundary = 750.0f;  // Minimum X position
    const float rightBoundary = 1200.0f; // Maximum X position
    const float patrolSpeed = 2.0f;     // Speed of movement

    if (bodyEnemy) {
        auto enemyB2Body = bodyEnemy->getBody();
        if (enemyB2Body) {
            // Determine direction and set velocity
            float velocityX = movingLeft ? -patrolSpeed : patrolSpeed;
            enemyB2Body->SetLinearVelocity(b2Vec2(velocityX, 0.0f));

            // Reverse direction at boundaries
            if (enemyX <= leftBoundary) {
                movingLeft = false; // Switch to moving right
            }
            else if (enemyX >= rightBoundary) {
                movingLeft = true; // Switch to moving left
            }
        }
    }

}











}

void AIComponentPatroling::drawDebugShape()
{
}
