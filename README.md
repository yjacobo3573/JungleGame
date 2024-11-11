




      As part of my Jungle game, I implemented all the basic components neccessary for my game to be fully functional, so all the components required were implemented in a similar way to the starter code. As part of my controller component, I specifically made the left and right arrow keys move the player back or forward. 
      Moreover, I added two additonal components which were super speed and a jump component. For super speed, I simply increased the players x velocity moving forward and I designated the key 's' to be used. 
      For my jump component, I simply increased the player's velocity in the y direction using the up arrow key. As of right now, this component isn't finished since I still need to implement gravity logic in order to bring the player down in a realistic way. This will be probably be fixed in the upcoming assignment. Additionally, I will add a jungle background later.

      Below is a video showing full functionality

[screen-capture (46).webm](https://github.com/user-attachments/assets/58730152-94f3-4655-adf6-8cbceb1bb65b)

   As part of Assignment 03 SDL2, I further developed my game and loaded all my textures from an xml file. Moreover, I implemented a view class that tracks the center of the view, scale, and rotation angle.
   I stored it statically and intialized it in the engine. Furthermore, I decided I wanted to specifically follow the player, so I decided to make another component named CameraFollower this class implements the update method by getting the body position of the player and the screen size in order to to update the Engines static member (View view) with the new values replacing the default values. 
   I also implemented frame rate limiting in my engine run method in order to have a smoother and more accurate game play. I also decided to load my background image and now you can see a glimpse of my game aesthetic moving forward.
[screen-capture (51).webm](https://github.com/user-attachments/assets/0fa78a03-186e-480c-8b5f-19fb5115f08b)
