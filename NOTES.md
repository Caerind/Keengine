# Scene :
###### Background : 
Color or Sprite  
Scaled texture or repeated texture  
Maybe create a class Background to use it both in Window and Scene ?  
Repeated texture need to not use sfml repeat : because not supported everywhere (old computer & smartphone) & you cannot use texture rect  
Access to sprite & rect to do tricked thing  
Need to add scene functions to manipulate the background and get data from it  


# Components
###### PhysicComponent
Faced an issue with updatePhysicShape()  
Problem is that onTransformNotified is called no matter which part change (ie even if Actor move)  
But the Fixture position is relative to the Body (ie Actor)  
So we need to update it ONLY if the transform of the component changes  
Another thing is that it can be harder to get the relative position if there is a node between the actor and the physic component  


# Serialization :
###### SceneComponent :
Children serialize their parent id, and they will be used on deserialization  
getParentId() & attachToParent(id)  