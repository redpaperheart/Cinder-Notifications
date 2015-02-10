#pragma once

#include "cinder/Timeline.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"

// boost error hack: http://forum.libcinder.org/topic/notificationcenter-in-cinder
#define BOOST_INTEL_STDCXX0X
#include <boost/signals2.hpp>

namespace rph {

    class Notification{
      public:
        //Notification(){};
        Notification( std::string msg);
        ~Notification(){};
        
        void draw();
        
        ci::Anim<float> time = 0.0f;
        std::string message;
        
        void animateIn();
        void animateOut();
        
        void die();
        
        void setYPos(float y);
        void setXPos(float x);
        
        float getWidth(){ return mWidth(); }
        float getHeight(){ return mHeight(); }
        
        boost::signals2::signal<void ()> signal_die;
        
        bool isDead(){ return mIsDead; }
        
      protected:
        ci::Anim<float> mX = 0;
        ci::Anim<float> mY = 0;
        ci::Anim<float> mWidth = 300;
        ci::Anim<float> mHeight = 0;
        float mSpace = 10.0f;
        
        ci::Anim<float> mAlpha = 0.0f;
        
        bool mIsDead;
        
        ci::TextBox mTextBox;
        ci::gl::TextureRef mTextBoxTexture;
        
    };
}