#include "AIComponentPatroling.h"

void AIComponentPatroling::draw()
{
}

void AIComponentPatroling::update()
{

float playerX;

for (auto& gameObjs : Engine::gameObjects) {

    if (gameObjs && gameObjs->getType() == "Player") { //if not null and type player

    auto body= gameObjs->get<BodyComponent>();
       if (body) {
            playerX= body->getX();
          }

     }
}

   float enemyX;
   float enemyVelocityX;

   auto bodyEnemy= parent().get<BodyComponent>();

   if (bodyEnemy) {
    enemyX= bodyEnemy->getX();
    enemyVelocityX= bodyEnemy->getVelocityX();
    }


  int distance;


  distance= enemyX-playerX;



if (distance >= 621)
{
    
    if (bodyEnemy)
    {
        auto enemyB2Body= bodyEnemy->getBody();
        if (enemyB2Body)
        {
            enemyB2Body->SetLinearVelocity(b2Vec2(-enemyVelocityX, 0.0f));
        }
    }

}









}

void AIComponentPatroling::drawDebugShape()
{
}
