#include "Notification.h"
 
namespace rph {
    
    Notification::Notification( std::string msg, ci::ColorA bg, ci::ColorA font){
        
        message = msg;
        
        mBgColor = bg;
        mFontColor = font;
        
        mTextBox.setColor(font);
        //mTextBox.setBackgroundColor(bg);
        mTextBox.setSize( ci::ivec2( mWidth-20, ci::TextBox::GROW ) );
        mTextBox.setText(message);
        
        ci::ivec2 sz = mTextBox.measure();
        mHeight = sz.y + 20;
        mY = -sz.y-20-10;
        
        mTextBoxTexture = ci::gl::Texture::create( mTextBox.render() );
        
    };
    
    void Notification::setYPos(float y){
        //mY = y;
        ci::app::timeline().apply(&mY, y, 0.3f);
    };
    void Notification::setXPos(float x){ mX = x; };
    
    void Notification::animateIn(){
        ci::app::timeline().apply(&mAlpha, 1.0f, 0.3f);
    };
    void Notification::animateOut(){
        ci::app::timeline().apply( &mAlpha, 0.0f, 0.3f ).finishFn( std::bind( &Notification::die, this) );
    };
    
    void Notification::die(){
        mIsDead = true;
        signal_die.emit( this );
    }
    
    //void Notification::setup(){}
    void Notification::draw(){
        ci::gl::ScopedMatrices mat;
        {
            ci::gl::ScopedColor c ( mBgColor * ci::ColorA(1.0f,1.0f,1.0f,mAlpha));
            ci::gl::drawSolidRect( ci::Rectf(mX,mY,mX+mWidth,mY+mHeight) );
        }
        ci::gl::translate(mX+10,mY+10);
        {
            ci::gl::ScopedColor c (ci::ColorA(1.0f,1.0f,1.0f,mAlpha));
            ci::gl::draw( mTextBoxTexture );
        }
    }

}
