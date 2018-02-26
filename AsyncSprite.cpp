//
//  AsyncSprite.cpp
//  CouponProject
//
//  Created by Ahmet Abak on 26.02.2018.
//

#include "AsyncSprite.hpp"
#include <chrono>

USING_NS_CC;

namespace asyncutils {
    template <typename T>
    std::string stringify(T value)
    {
        std::ostringstream os;
        os << value ;
        return os.str();
    }
    
    long long get_time() {
        using namespace std::chrono;
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        return ms.count();
    }
}

void AsyncSprite::onDownloadCompleted(const cocos2d::network::DownloadTask &task) {
    
    std::string name = "__asyncSprite__" + srcID;
    std::string filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + name;
    
    initWithFile(filePath);
    
    setScale(originalSize.width / getTextureRect().size.width, originalSize.height / getTextureRect().size.height);
    
    delete downloader;
}

AsyncSprite* AsyncSprite::createFromURL(const std::string& url,const cocos2d::Size& size, const std::string& placeholder) {
    AsyncSprite *pRet = new(std::nothrow) AsyncSprite();
    if (pRet && pRet->initFromURL(url, size, placeholder)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool AsyncSprite::initFromURL(const std::string url, cocos2d::Size size, std::string placeholder) {
    
    using namespace cocos2d::network;
    
    if (!Sprite::init()) {
        return false;
    }
    
    originalSize = size;
    initWithFile(placeholder);
    setScale(originalSize.width / getTextureRect().size.width, originalSize.height / getTextureRect().size.height);
    
    srcID = asyncutils::stringify(asyncutils::get_time());
    
    downloader = new (std::nothrow) Downloader();
    downloader->setOnFileTaskSuccess(CC_CALLBACK_1(AsyncSprite::onDownloadCompleted, this));
    downloader->setOnTaskError([this](const DownloadTask &t, int a, int b, const std::string &st) {
        delete this->downloader;
    });
    downloader->setOnTaskProgress([](const DownloadTask &t, int64_t current_d, int64_t total_d, int64_t total_expect){
        cocos2d::log("%llu %llu %llu", current_d, total_d, total_expect);
    });
    
    std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath() + "__asyncSprite__" + srcID;
    downloader->createDownloadFileTask(url, filepath);
    
    return true;
}

AsyncSprite::~AsyncSprite() {
    if (downloader) {
        delete downloader;
    }
    std::string name = "__asyncSprite__" + srcID;
    std::string filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + name;
    
    FileUtils::getInstance()->removeFile(filePath);
}
