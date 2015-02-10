#include "Notification.h"
 
namespace rph {
    
    Notification::Notification( std::string msg){
        
        message = msg;
        
        mTextBox.setColor(ci::ColorA(1,1,1,1));
        //mTextBox.setBackgroundColor(ci::ColorA(1,0,0,1));
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
        ci::app::timeline().apply( &mAlpha, 0.0f, 0.3f ).finishFn( boost::bind( &Notification::die, this) );
    };
    
    void Notification::die(){
        mIsDead = true;
        signal_die();
    }
    
    //void Notification::setup(){}
    void Notification::draw(){
        ci::gl::pushMatrices();
        ci::gl::color(ci::ColorA(0,0,0,mAlpha));
        ci::gl::drawSolidRect( ci::Rectf(mX,mY,mX+mWidth,mY+mHeight) );
        ci::gl::color(ci::ColorA(1,1,1,mAlpha));
        
        ci::gl::translate(mX+10,mY+10);
        ci::gl::draw( mTextBoxTexture );
        ci::gl::popMatrices();
    }

}