# BubbleBusters / BubbleWatch

BubbleBusters is a game created using the FPS/C++ template from UE4.

In BubbleBusters the player will have to confront his fears and fight with his gun the ghosts that will appear around the map.

The only problem is that this is a not a normal gun and these are not normal ghosts.
In fact, these ghosts are known as *bubble ghosts* and the only way to get rid of them is using the player gun that is charged with bubbles (of course).

In order to beat up the ghosts the player will need to shot them with bubbles the same color as their body (for example for a blue ghost, the player will need to shot a blue bubble).
Also the player will need to be careful because if a bubble of a different color touch a ghost, the bubble will be converted in another ghost.

### Main Rules ###

- The player can move and is equipped with a bubble gun.
- The bubble gun has ilimited ammo.
- The bubble colours of the gun appear randomly making the user to loose some shots in order to destroy the correct ghost.
- Bubbles can bounce around the map making this a mechanic where the user can use the map to shot a ghost.
- If two bubbles of different color collide each other, they will become a ghost also.
- The number of spawned ghosts at the beginning is predefined.
- The colours of the ghosts are selected randomly.
- In order to win the user will need to clean the map from all the ghosts.
- Every time a ghost comes to close to the user, the user loose some health. Once the health is below zero means Game Over.

Ideas for the future
---
- Add FX, music and animations
- Add some kind of limitator on the ammo of the gun, making the user think more which is going to be their next shot.
-- With limited ammo some object in order to recover ammo.
- Add Health powerup in order to recover health
- Add more ghosts types 
- Add more bubble types

### Implementation / Code ###

I think that the easiest way to explain how and why I implemented the things as I did is dividing it as the structure that I have inside the Project.

- Bubble
- Components
- Pool
- Spawn
- Character

#### Bubble #####

*Behind the final idea*

The main feature of the game was based on the game Puzzle Bobble where a dinosaur was shooting colour bubbles to destroy another before they crush him.

At the beginning the idea was to create more or less the same game but in 3D. Some of the original ideas were:
- Create puzzles using bubbles, for example inside a room, the door is a bubble wall and in order to go out the player will need to destroy the bubbles using the correct colors (Tutorial: A door using only blue bubbles if the user shot a red bubble nothing happen, but when using a bubble one, all the bubbles are destroyed and can pass).
- Add a cube in the middle (formed by bubbles) and destroy it in a certain time or before the room was filled with bubbles.

Those were the first ideas and the first tests were an open map with a big cube in the middle, in order to solve the puzzles I started to think which could be the best way to solve the bubble collisions eficiently. Thinking on the main inspiration, Puzzle Bobble, the easiest way was to create a BubbleManager for saving the position of the bubbles and iterate through them using an A* algorithm or some other in order to solve it.

In the end since what I wanted to show for the test is that I know how to use Unreal I thought that the best way was making a game a bit more dynamic, it is then when I started with the idea that the bubbles can move and you should beat them.

*Code*

In the game almos everything is a bubble that's why I started creating a Bubble interface which later will be used by the ProjectileBubbles and the Ghosts.

- Bubble: Interface defining the basic functions any bubble should have (Enable, Disable, Setters and Getters for the colors).
- ProjectileBubble: AActor used to be shot from the gun, is able to bounce around the map and has the logic to disable another bubble or to spawn a new enemy.
- Ghost: ACharacter based also on the bubble interface has only enable and disable logic since is an enemy that is controlled using a behaviour tree.

#### Components ####

Currently in the game there is only one component: the *HealthComponent*.
This component is in charge of the health of its owner, it also counts with a delegate to detect when the health is below zero.
In my case, the Character is binded to this delegate and acts properly.

#### Pool ####

Since the game is spawning bubbles all the time, as ammo for the bubble gun or as ghosts during the game I thought that instead of spawning actors all the time will be more useful use the *Object Pool* optimization pattern (https://gameprogrammingpatterns.com/object-pool.html).

The pool implementation is divided in 3 classes:

1) BubblePool: Is the father of all the pools it only has the most basic logic, initialization and an array using the Bubble interface meaning that these pool can be used for any UObject that implements these interface.

2) BubbleProjectilePool: Is a static pool with a defined number of elements, every time that the character shots a bubble one bubble is activated from the pool and once it is disabled it comes back to the array.

3) GhostPool: Is a dinamic pool, with dinamic I mean that since during the game the number of ghosts can grow a lot it is using an array but as an stack meaning that everytime we activate a ghost this one is popped out the array and once a ghost is disables is pushed back in, meaning that we only spawn ghosts once the number of ghosts in the map is already the size of the pool.

#### Spawn ####

In order to spawn the enemies in a proper location in the game I created an Enemy Spawner that thanks to the GhostPool has grown quite a lot and is taking care to use the GhostPool as a dinamic pool.

#### Character ####

Since I wanted to spawn a different kind of ammo, but I wanted to get all the functionalities from the Template I decided to tweak a little bit the original character from the template in order to create a son that I can customize as I want.

### Implementation / Blueprints ###

#### AI ####

The AI is a Behaviour using BTServices, BlackBoards and AIPerception.

The behaviour is more or less as follows, when is spawned the AI will start moving randomly across the map until is able to see the Player (using the perception component) and once has seen the Player it will follow him until is able to hit it, once has hitted the Player it will go back again until is able to find the Player back.

I'm using the BlackBoard to set the Random Location (with the help of a BTService) and also to save the character once it has been seen.

#### UI ####

I added a really basic UI just to add a brief introduction and to have some feedback to know when the user has lost or win. 



