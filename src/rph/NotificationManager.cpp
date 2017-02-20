#include "NotificationManager.h"

namespace rph {
    
    NotificationManager* NotificationManager::m_pInstance = NULL;
    NotificationManager* NotificationManager::getInstance(){
        if (!m_pInstance){ // Only allow one instance of class to be generated.
            m_pInstance = new NotificationManager;
            m_pInstance->mWindowSize = ci::app::getWindowSize();
        }
        return m_pInstance;
    }
    
    Notification * NotificationManager::add(std::string message, float timeout, ci::ColorA bgColor, ci::ColorA fontColor){
        Notification *n = new Notification( message, bgColor, fontColor );
        mNotifications.push_back(n);
        
        n->animateIn();
        
        updateYPos();
        
        ci::app::timeline().apply( &n->time, timeout, timeout ).finishFn(std::bind( &Notification::animateOut, n));
        //n->signal_die.connect(std::bind( &NotificationManager::deleteNotification, this, n));
        n->signal_die.connect(std::bind( &NotificationManager::deleteNotification, this, std::placeholders::_1));
//        n->signal_die.connect([&](Notification * n){ deleteNotification(n);} );
        return n;
    }
    
    void NotificationManager::deleteNotification( Notification *n ){
        //possibly remove the connected signal here?
        //ci::app::console() << mNotifications.size() << "- about to remove :" << n->message << std::endl;
        mNotifications.remove(n);
        //ci::app::console() << mNotifications.size() << "- removed: " << n->message << std::endl;
        updateYPos();
        //delete n; //currently throws an error.
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
        //ci::gl::translate(ci::app::getWindowWidth()-310, 10);
        ci::gl::translate(mWindowSize.x-310, 10);
        for (auto notification : mNotifications){
            notification->draw();
        }
        ci::gl::popMatrices();
    }

}
