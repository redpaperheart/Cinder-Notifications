#include "NotificationManager.h"

namespace rph {
    
    NotificationManager* NotificationManager::m_pInstance = NULL;
    NotificationManager* NotificationManager::getInstance(){
        if (!m_pInstance){ // Only allow one instance of class to be generated.
            m_pInstance = new NotificationManager;
//            m_pInstance->setup();
        }
        return m_pInstance;
    }
//    void NotificationManager::setup(){}
    
    Notification * NotificationManager::add(std::string message, float timeout, ci::ColorA bgColor, ci::ColorA fontColor){
        Notification *n = new Notification( message, bgColor, fontColor );
        mNotifications.push_back(n);
        
        n->animateIn();
        
        updateYPos();
        
        ci::app::timeline().apply( &n->time, timeout, timeout ).finishFn(boost::bind( &Notification::animateOut, n));
        n->signal_die.connect(boost::bind( &NotificationManager::deleteNotification, this, n));
        return n;
    }
    
    void NotificationManager::deleteNotification( Notification *n ){
        //possibly remove the connected signal here?
        mNotifications.remove(n);
        updateYPos();
    }
    
    
    void NotificationManager::updateYPos(){
        int totalHeight = 0;
        int spaceY = 5;
        for ( std::list<rph::Notification *>::reverse_iterator it = mNotifications.rbegin(); it != mNotifications.rend(); it++){
            (*it)->setYPos( totalHeight );
            totalHeight += (*it)->getHeight() + spaceY;
        }
    }
    
    
    void NotificationManager::draw(){
        if(mNotifications.size()<1)return;
        
        ci::gl::pushMatrices();
        ci::gl::translate(ci::app::getWindowWidth()-310, 10);
        for (auto notification : mNotifications){
            notification->draw();
        }
        ci::gl::popMatrices();
    }

}