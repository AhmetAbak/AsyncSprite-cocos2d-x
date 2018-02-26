//
//  AsyncSprite.hpp
//  CouponProject
//
//  Created by Ahmet Abak on 26.02.2018.
//

#ifndef AsyncSprite_hpp
#define AsyncSprite_hpp

#include <string>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class AsyncSprite : public cocos2d::Sprite {
private:
    cocos2d::network::Downloader *downloader;
    std::string srcID;
    cocos2d::Size originalSize;
    void onDownloadCompleted(const cocos2d::network::DownloadTask &task);
public:
    CREATE_FUNC(AsyncSprite);
    static AsyncSprite* createFromURL(const std::string& url, const cocos2d::Size& size, const std::string& placeholder);
    bool initFromURL(const std::string url, cocos2d::Size size, std::string placeholder);
    ~AsyncSprite();
};
#endif /* AsyncSprite_hpp */
