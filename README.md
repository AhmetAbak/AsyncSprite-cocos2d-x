# AsyncSprite-cocos2d-x
Asynchronous image loading class for cocos2d-x. 
Simply downloads image and shows it in ```Sprite```.

Sample usage:
```
AsyncSprite *as = AsyncSprite::createFromURL("image_url", size, "placeholder.png");
as->setPosition(position);
addChild(as);
```


