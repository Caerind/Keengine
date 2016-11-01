# Scene :
###### Background : 
Color or Sprite  
Scaled texture or repeated texture  
Maybe create a class Background to use it both in Window and Scene ?  
Repeated texture need to not use sfml repeat : because not supported everywhere (old computer & smartphone) & you cannot use texture rect  
Access to sprite & rect to do tricked thing  
Need to add scene functions to manipulate the background and get data from it  



# Serialization :
###### SceneComponent :
Children serialize their parent id, and they will be used on deserialization  
getParentId() & attachToParent(id)  